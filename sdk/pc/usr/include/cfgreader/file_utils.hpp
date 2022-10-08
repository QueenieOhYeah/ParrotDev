/**
 * Copyright (C) 2019 Parrot Drones SAS
 */

#ifndef CFGREADER_FILE_UTILS_HPP__
#define CFGREADER_FILE_UTILS_HPP__

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

namespace cfgreader {

std::string join(std::string &s1, std::string &s2)
{
    if (s1 == "")
        return s2;
    if (s2 == "")
        return s1;
    return s1 + "." + s2;
}

std::vector<std::string> splitString(const std::string &s, char delimiter)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, delimiter))
        tokens.push_back(item);
    return tokens;
}

void removeSpaces(std::string &s)
{
    std::string::iterator end_pos = std::remove(s.begin(), s.end(), ' ');
    s.erase(end_pos, s.end());
}

bool fileExists(const std::string& path)
{
    struct stat s;
    return (stat(path.c_str(), &s) == 0);
}

bool fileIsRegular(const std::string& path)
{
    struct stat s;
    return (stat(path.c_str(), &s) == 0) && S_ISREG(s.st_mode);
}

bool fileIsDirectory(const std::string& path)
{
    struct stat s;
    return (stat(path.c_str(), &s) == 0) && S_ISDIR(s.st_mode);
}

std::string getSingleLineFileContent(const std::string& path)
{
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        if (std::getline(file, line))
            return line;
    }
    return "";
}

}
#endif
