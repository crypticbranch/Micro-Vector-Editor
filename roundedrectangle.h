#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include "Rectangle.h"

class RoundedRectangle : public Rectangle
{
public:
    int rx = 12;
    int ry = 12;
    RoundedRectangle() = default;
    RoundedRectangle(int x1, int y1, int rx = 12, int ry = 12);
    void draw(QPainter& painter) override;
    std::unique_ptr<Objects> clone() const override;
    std::string toSVG() const override ;
};

#endif // ROUNDEDRECTANGLE_H
