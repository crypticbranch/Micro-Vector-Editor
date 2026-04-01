#ifndef FREEHAND_H
#define FREEHAND_H
#include "Objects.h"
#include <vector>

class FreeHand : public Objects {
public:
    std::vector<QPoint> points;

    void draw(QPainter& painter) override ;
    void setEnd(int x2, int y2) override ;
    void move(int dx, int dy) override ;
    bool contains(int px, int py) const override ;
    std::unique_ptr<Objects> clone() const override ;
    void resize(int dx, int dy) override ;
    QRect getBoundingBox() const override;
    std::string toSVG() const override ;
};

#endif // FREEHAND_H
