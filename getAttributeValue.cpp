#include <string>
#include "getAttributeValue.h"

std::string getAttributeValue(const std::string &Line, const std::string &attributeName)
{
    std::string searchStr = attributeName + "=\"";
    size_t startPos = Line.find(searchStr);
    if (startPos == std::string::npos)
    {
        return "";
    }
    startPos += searchStr.length();
    size_t endPos = Line.find("\"", startPos);
    if (endPos == std::string::npos)
    {
        return "";
    }
    return Line.substr(startPos, endPos - startPos);
}
