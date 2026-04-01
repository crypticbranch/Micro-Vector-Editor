#ifndef TEXT_H
#define TEXT_H
#include "Objects.h"

class Text : public Objects {
public:
    int x, y;
    QString content;
    int font_size = 12;

    void draw(QPainter& painter) override ;

    void setEnd(int x2, int y2) override ;

    void move(int dx, int dy) override ;

    bool contains(int px, int py) const override ;
    std::unique_ptr<Objects> clone() const override ;

    void resize(int dx, int dy) override ;
    QRect getBoundingBox() const override ;
    std::string toSVG() const override ;
};

#endif // TEXT_H
