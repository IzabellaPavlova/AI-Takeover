#include "Constants.h"

Constants::Constants() {}
Constants::~Constants() {}

bool Constants::read_file(const std::string &f_name /* =".config" */)
{
    std::string line;
    std::ifstream file(f_name);
    if (!file.is_open())
        return false;

    while (std::getline(file, line))
    {
        try
        {
            parse_line(line);
        }
        catch (const boost::bad_lexical_cast &e)
        {
            std::cerr << e.what() << " (File : '" << f_name << "' ; line : '" << line << ")'\n";
            return false;
        }
    }

    return true;
}

float Constants::at(const std::string &key) const
{
    try
    {
        float value = m_map.at(key);
        return value;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Constant " << key << " not found in\n";
        throw(e);
    }
}

void Constants::parse_line(const std::string &line)
{
    std::istringstream is_line(line);
    std::string key;
    if (std::getline(is_line, key, '='))
    {
        std::string str_value;
        is_line >> str_value;
        float value = boost::lexical_cast<float>(str_value);
        m_map[key] = value;
    }
}