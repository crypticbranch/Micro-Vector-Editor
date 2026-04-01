#ifndef LINE_H
#define LINE_H

#include "Objects.h"

class Line : public Objects
{
public:
    int x1;
    int y1;
    int x2;
    int y2;

    void draw(QPainter& painter) override ;
    void setEnd(int x2, int y2) override ;
    std::unique_ptr<Objects> clone() const override ;
    bool contains(int px, int py) const override ;
    void move(int dx, int dy) override ;
    void resize(int dx, int dy) override ;
    QRect getBoundingBox() const override ;
    std::string toSVG() const override ;
};

#endif // LINE_H
