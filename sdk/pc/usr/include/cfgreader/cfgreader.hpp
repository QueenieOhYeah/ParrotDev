/**
 * Copyright (C) 2019 Parrot Drones SAS
 */

#ifndef CFGREADER_HPP__
#define CFGREADER_HPP__

#include <libconfig.h++>

#include "cfgreader-ulog.hpp"
#include "param_set.hpp"

#include <errno.h>
#include <list>
#include <string>
#include <memory>
#include <algorithm>

namespace cfgreader
{

class Config {
public:
    std::string mFile;
    std::string mInclude;

    Config(const std::string &file, const std::string &include = ""):
        mFile(file), mInclude(include) { }
};

/**
 * Trait SettingReader<T> know how to read a T from a Setting.
 */
template <typename T> struct SettingReader {
    /** Set place with the value of the Setting set of type T. */
    static int read (const libconfig::Setting& set, T& place);
};

class NothrowConfig : public libconfig::Config {
public:
    bool hasErrors() { return mHasErrors; }

protected:
    virtual void handleError() override;

private:
    bool mHasErrors = false;
};

/**
 * ConfigReader instances may be initialized by setting both following
 * environment variables:
 *
 *   - CFGREADER_VARIANT (path to directory holding root.cfg file)
 *   - CFGREADER_MODE (subdirectory containing init.cfg)
 */
class ConfigReader {
private:
    static const std::string DEFAULT_CFG_DIR_PATH;

    /* Order matters: elements in front of the list are the ones which
       are loaded LAST, and shadow configurations loaded earlier (at
       the end of the list); see ConfigReader::getSetting. */
    std::list<Config> mConfigurationList;

    /* Same order as mConfigurationList. */
    std::list<std::unique_ptr<NothrowConfig>> mConfigList;

    void addConfiguration(
        const std::string &path,
        const std::string &droneVariant,
        const std::string &runningMode);

    /*
     * @param[in] : name of the configuration parameter to get
     *
     * @return : the libconfig setting associated with that parameter (either
     * fetched from the common files or from the variant specific files)
     */
    const libconfig::Setting &getSetting(const char *name);

    /*
     * @param[in] name : name of the configuration parameter to look for in
     * common and variant-specific files
     *
     * @return true iff the parameter exists
     */
    /* FIXME: in fact exists() should be like find() and return an
     * iterator, to avoid doing a linear search twice.
     */
    bool exists(const char *name);

    /*
     * Read setting set into a set of parameters of type T.
     */
    template <typename T>
        static int read(const libconfig::Setting& set_root, ParamSet<T>& f_s)
    {
        int ret = 0;

        if (!set_root.isGroup()) {
            logW("Sets of parameters %s should be defined as 'group' type",
                set_root.getName() ? set_root.getName() : "unknown");
            ret = -EINVAL;
        } else {
            for (int i = 0; i < set_root.getLength(); i++) {
                const libconfig::Setting &curr = set_root[i];
                T currVal = {};

                std::string currVariantName = curr.getName();

                int read_ret = SettingReader<T>::read(curr, currVal);
                if (read_ret < 0)
                    ret = read_ret;
                f_s[currVariantName] = currVal;
            }
            if (set_root.getLength() == 0) {
                /* assume a group without values is an error, see also the check in paramset.hpp */
                logC("%s is empty", set_root.getName() ? set_root.getName() : "unknown");
            }
            f_s.name = set_root.getName();
        }

        return ret;
    };

    /*
     * Read setting set into place of type T.
     */
    template <typename T>
        static int read(const libconfig::Setting& set, T& place)
    {
        const SettingReader<T> reader;
        return reader.read(set, place);
    };

public:

    template <typename T>
        static int getField(const libconfig::Setting& set, const char *fieldName, T& f)
    {
        if (!set.exists(fieldName)) {
            logW("Could not find field %s in setting %s", fieldName,
                set.getName());
            return -ENOENT;
        } else {
            return read(set[fieldName],f);
        }
    }

    // no env. variable impacts this constructor, just read from a file.
    ConfigReader(const Config &config);

    // legacy behaviour, with env. variables and by default hard-coded
    // /etc/colibry path
    ConfigReader(const std::string &path = DEFAULT_CFG_DIR_PATH);

    ~ConfigReader() {};

    /*
     * Load configuration for the drone variant and modes passed in
     * constructor
     *
     * @return : 0 in case of success
     *           -ENOENT if no configuration file was found
     */
    int load();

    /*
     * If defined, prepend the root directory to a given input path.
     * If not defined, keep the input path untouched.
     *
     * @param[in] the input path
     *
     * @return : the prepended path
     */
    static std::string insertRootDir(const std::string &path);

    /*
     * Get value of a given parameter
     *
     * @param[in] name : name of the parameter in the config files
     * @param[out] val : value that should be set according to the parameter
     *
     * @return : 0 in case of success,
     *           -EINVAL if a parameter of the same name was found, but with
     * a type mismatch,
     *           -ENODATA if the parameter was not found,
     *           -ENOENT if the parameter was found but some of its fields
     * were missing
     */
    template <typename T>
    int get(const char* name, T& val)
    {
        if (exists(name)) {
            return read(getSetting(name), val);
        } else {
            logW("Could not find %s in cfg file", name);
            return -ENODATA;
        }
    };

    /*
     * Get value of a given parameter set
     *
     * @param[in] name : name of the parameter set in the config files
     * @param[out] set : set of values that will be updated according to
     * the parameter set found in config
     *
     * @return : 0 in case of success,
     *           -EINVAL if a parameter set of the same name was found, but
     * with a type mismatch,
     *           -ENODATA if the parameter set was not found,
     *           -ENOENT if the parameter set was found but some of its
     * fields were missing
     */
    template <typename T>
    int get(const char* name, ParamSet<T>& set)
    {
        if (exists(name)) {
            return read(getSetting(name), set);
        } else {
            logW("Could not find set %s in cfg file", name);
            return -ENODATA;
        };
    };

    /*
     * Set config parameter according to the init value of a given parameter
     * set
     *
     * @param[in] set : parameter set to use
     * @param[out] val : value that should be set
     *
     * @return : 0 in case of success,
     * exist in the param set,
     *           -ENOENT if the init setter was not found
     */
    template <typename T>
    int getInitValue(ParamSet<T>& set, T& val, std::string initValueName)
    {
        int ret = 0;
        if (!set.exists(initValueName)) {
            logW("Cannot find %s in %s", initValueName.c_str(),
                set.name.c_str());
            ret = -ENOENT;
        } else {
            val = set[initValueName];
        }
        return ret;
    }

    const std::list<Config> &getConfigurationList() {
        return mConfigurationList;
    }

};

} // namespace

#endif /* __CONFIG_READER_HPP__ */
