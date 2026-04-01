#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Objects.h"

class Rectangle : public Objects
{
public:
    int x;
    int y;
    int width;
    int height;
    void draw(QPainter& painter) override;
    void setEnd(int x2, int y2) override ;
    bool contains(int px, int py) const override ;
    std::unique_ptr<Objects> clone() const override;
    void move(int dx, int dy)override;
    void resize(int dx, int dy) override ;
    QRect getBoundingBox() const override ;
    std::string toSVG() const override ;
};
#endif // RECTANGLE_H
