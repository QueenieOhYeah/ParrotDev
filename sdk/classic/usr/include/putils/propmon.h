/**
 * @file propmon.h
 *
 * @brief Everything needed to monitor properties through netlink sockets.
 *         Provides multicast and monitoring APIs.
 *
 * @author eric.brunet@parrot.com
 *
 * @copyright Copyright (C) 2016 Parrot S.A.
 */

#ifndef _PROPMON_H_
#define _PROPMON_H_

#include "putils/properties.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************
 *
 * Multicast API, intended to be only used
 * by the init process
 *
 ************************************************/

/* Forward declaration */
struct propmc;

/**
 * @brief Create an interface to multicast a properties' changes
 *
 * @return Handle on the interface on success, otherwise NULL
 */
struct propmc *propmc_new(void);

/**
 * @brief Destroy a multicast interface
 *
 * @param[in] pmc Handle on the interface
 */
void propmc_destroy(struct propmc *pmc);

/**
 * @brief Multicast a property change
 *
 * @param[in] pmc Handle on the multicast interface
 * @param[in] name The property key
 * @param[in] value The property new value
 *
 * @return 0 on success, otherwise negative errno
 */
int propmc_send(struct propmc *pmc, const char *name, const char *value);

/************************************************
 *
 * Monitoring API
 *
 ************************************************/

struct property_change {
	char key[SYS_PROP_KEY_MAX];
	char value[SYS_PROP_VALUE_MAX];
};

/* Forward declaration */
struct propmon;

/**
 * @brief Create an interface to monitor properties' changes
 *
 * @return Handle on the interface on success, otherwise NULL
 */
struct propmon *propmon_new(void);

/**
 * @brief Start monitoring interface.
 *
 * @param[in] pmon Handle on the monitoring interface
 *
 * @return 0 on success, a negative errno otherwise
 */
int propmon_start(struct propmon *pmon);

/**
 * @brief Destroy a monitoring interface
 *
 * @param[in] pmon Handle on the monitoring interface
 */
void propmon_destroy(struct propmon *pmon);

/**
 * @brief Get file descriptor of the interface
 *
 * @param[in] pmon Handle on the monitoring interface
 *
 * @return Negative errno on error, otherwise the file descriptor
 *
 * @remarks The returned file descriptor has O_NONBLOCK and O_CLOEXEC flags set.
 */
int propmon_get_fd(struct propmon *pmon);

/**
 * @brief Add a pattern to the filter list. One of all the provided patterns
 *           has to match with a part of the property name ("." is used as
 *           separator) or with the entire property name for the monitoring
 *           interface to be notified of the property's changes
 *
 *    For example :
 *       1- property "toto.toto2" will match with :
 *              - "toto"
 *              - "toto2"
 *              - "toto.toto2"
 *       2- property "toto.toto2.toto3" will match with :
 *              - "toto"
 *              - "toto2"
 *              - "toto3"
 *              - "toto.toto2.toto3"
 *
 * @notice All wanted matches have to be passed before propmon_start()
 * @notice If no pattern is provided, all properties will be notified
 *
 * @param[in] pmon Handle on the monitoring interface
 * @param[in] pattern The pattern that needs to match
 *
 * @return 0 on success, otherwise negative errno
 */
int propmon_add_filter_match(struct propmon *pmon, const char *pattern);

/**
 * @brief Read a property change.
 *
 * @notice As property's names are not normalized, one should ALWAYS verify
 *           returned pch.key is not a false positive due to another property,
 *           even if the entire name is given as a filter.
 *    For example :
 *       - One is interested by property "drone" and register a match on it
 *       - Property "ro.build.drone.hardware.revision" is modified.
 *       -> User will be notified of this change
 *
 * @param[in] pmon Handle on the monitoring interface
 * @param[out] pch The new property value
 *
 * @return 0 on success, otherwise negative errno
 * @return -EAGAIN if no property change is in the queue.
 */
int propmon_receive(struct propmon *pmon, struct property_change *pch);

#ifdef __cplusplus
}
#endif

#endif /* _PROPMON_H_ */
