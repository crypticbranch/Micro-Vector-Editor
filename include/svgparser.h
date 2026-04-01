#ifndef SVGPARSER_H
#define SVGPARSER_H
#include <vector>
#include <memory>
#include <string>
#include "Objects.h"

std::vector<std::unique_ptr<Objects>> parseSVG(const std::string& filename);


#endif // SVGPARSER_H
