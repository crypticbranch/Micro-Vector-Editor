#include <string>
#include "toInt.h"

int toInt(const std::string &str, int defaultValue)
{
    if (str.empty())
        return defaultValue;
    return std::stoi(str);
}
