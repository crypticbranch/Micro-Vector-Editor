#ifndef CIRCLE_H
#define CIRCLE_H

#include "Objects.h"
#include<QPainter>

class Circle : public Objects
{
public:
    int cx;
    int cy;
    int r;
    void draw(QPainter& painter) override ;
    void setEnd(int x2, int y2) override ;
    std::unique_ptr<Objects> clone() const override ;
    bool contains(int px, int py) const override;
    void move(int dx, int dy) override ;
    void resize(int dx, int dy) override ;
    QRect getBoundingBox() const override ;
    std::string toSVG() const override ;
};

#endif // CIRCLE_H

