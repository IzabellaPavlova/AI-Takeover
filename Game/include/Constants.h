#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <unordered_map>
#include <iostream>

class Constants
{
public:
    Constants();
    ~Constants();
    Constants(const Constants &) = default;
    Constants(Constants &&) noexcept = delete;
    Constants &operator=(const Constants &) = delete;
    Constants &operator=(Constants &&) noexcept = delete;

    bool read_file(const std::string &f_name = ".config") noexcept;
    float at(const std::string &key) const;

private:
    void parse_line(const std::string &line);
    std::unordered_map<std::string, float> m_map;
};