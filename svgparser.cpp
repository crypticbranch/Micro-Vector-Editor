#include "svgparser.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "getAttributeValue.h"
#include "toInt.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Text.h"
#include "Hexagon.h"
#include "FreeHand.h"
#include "roundedrectangle.h"

std::vector<std::unique_ptr<Objects>> parseSVG(const std::string& filename){
    std::vector<std::unique_ptr<Objects>> shapes;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "FAILED to open SVG file: " << filename << "\n";
        return shapes;
    }
    std::string line;
    while (std::getline(file, line)){
        if (line.find("<rect") != std::string::npos){
            std::string rxVal = getAttributeValue(line, "rx");
            std::string ryVal = getAttributeValue(line, "ry");
            if (!rxVal.empty() || !ryVal.empty()) {
                auto rrect = std::make_unique<RoundedRectangle>();
                rrect->x = toInt(getAttributeValue(line, "x"));
                rrect->y = toInt(getAttributeValue(line, "y"));
                rrect->width = toInt(getAttributeValue(line, "width"));
                rrect->height = toInt(getAttributeValue(line, "height"));
                rrect->rx = toInt(rxVal);
                rrect->ry = toInt(ryVal);
                rrect->fill = getAttributeValue(line, "fill");
                rrect->stroke = getAttributeValue(line, "stroke");
                rrect->stroke_width = toInt(getAttributeValue(line, "stroke-width"), 1);
                shapes.push_back(std::move(rrect));
            }else{
                auto rect = std::make_unique<RoundedRectangle>();
                rect->x = toInt(getAttributeValue(line, "x"));
                rect->y = toInt(getAttributeValue(line, "y"));
                rect->width = toInt(getAttributeValue(line, "width"));
                rect->height = toInt(getAttributeValue(line, "height"));
                rect->rx = toInt(rxVal);
                rect->ry = toInt(ryVal);
                rect->fill = getAttributeValue(line, "fill");
                rect->stroke = getAttributeValue(line, "stroke");
                rect->stroke_width = toInt(getAttributeValue(line, "stroke-width"), 1);
                shapes.push_back(std::move(rect));
            }
        }else if (line.find("<circle") != std::string::npos){
            auto c = std::make_unique<Circle>();
            c->cx = toInt(getAttributeValue(line, "cx"));
            c->cy = toInt(getAttributeValue(line, "cy"));
            c->r = toInt(getAttributeValue(line, "r"));
            c->fill = getAttributeValue(line, "fill");
            c->stroke = getAttributeValue(line, "stroke");
            c->stroke_width = toInt(getAttributeValue(line, "stroke-width"), 1);
            shapes.push_back(std::move(c));
        }else if (line.find("<line") != std::string::npos){
            auto l = std::make_unique<Line>();
            l->x1 = toInt(getAttributeValue(line, "x1"));
            l->y1 = toInt(getAttributeValue(line, "y1"));
            l->x2 = toInt(getAttributeValue(line, "x2"));
            l->y2 = toInt(getAttributeValue(line, "y2"));
            l->stroke = getAttributeValue(line, "stroke");
            l->stroke_width = toInt(getAttributeValue(line, "stroke-width"), 1);
            shapes.push_back(std::move(l));
        }else if (line.find("<text") != std::string::npos){
            auto text = std::make_unique<Text>();
            text->x = toInt(getAttributeValue(line, "x"));
            text->y = toInt(getAttributeValue(line, "y"));
            text->stroke = getAttributeValue(line, "stroke");
            text->stroke_width = toInt(getAttributeValue(line, "stroke-width"), 1);
            text->fill = getAttributeValue(line, "fill");
            size_t startPos = line.find(">");
            size_t endPos = line.find("</text>");
            if (startPos != std::string::npos && endPos != std::string::npos && endPos > startPos){
                text->content = QString::fromStdString(line.substr(startPos + 1, endPos - startPos - 1));
            }
            shapes.push_back(std::move(text));
        }else if (line.find("<polygon") != std::string::npos) {
            auto hex = std::make_unique<Hexagon>();
            hex->fill = getAttributeValue(line, "fill");
            hex->stroke = getAttributeValue(line, "stroke");
            hex->stroke_width = toInt(getAttributeValue(line, "stroke-width"), 1);
            std::string points = getAttributeValue(line, "points");
            std::stringstream ss(points);
            std::string pair;
            std::vector<QPoint> pts;
            while (ss >> pair) {
                size_t comma = pair.find(',');
                if (comma != std::string::npos) {
                    pts.push_back(QPoint(std::stoi(pair.substr(0, comma)),
                                         std::stoi(pair.substr(comma + 1))));
                }
            }
            if (!pts.empty()) {
                // Approximate center and radius from points
                hex->cx = (pts[0].x() + pts[3].x()) / 2;
                hex->cy = (pts[0].y() + pts[3].y()) / 2;
                hex->r = std::sqrt(std::pow(pts[0].x() - hex->cx, 2) + std::pow(pts[0].y() - hex->cy, 2));
            }
            shapes.push_back(std::move(hex));
        }else if (line.find("<polyline") != std::string::npos) {
            auto freeh = std::make_unique<FreeHand>();
            freeh->stroke = getAttributeValue(line, "stroke");
            freeh->stroke_width = toInt(getAttributeValue(line, "stroke-width"), 1);

            std::string points = getAttributeValue(line, "points");
            std::stringstream ss(points);
            std::string pair;
            while (ss >> pair) {
                size_t comma = pair.find(',');
                if (comma != std::string::npos) {
                    freeh->points.push_back(QPoint(std::stoi(pair.substr(0, comma)),
                                                std::stoi(pair.substr(comma + 1))));
                }
            }
            shapes.push_back(std::move(freeh));
        }
    }
    return shapes;
}
