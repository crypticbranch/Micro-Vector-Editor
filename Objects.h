#ifndef OBJECTS_H
#define OBJECTS_H
#include <string>
#include<QPainter>

class Objects
{
public:
    virtual void resize(int dx, int dy) = 0;
    std::string stroke = "black";
    std::string fill = "none";
    int stroke_width = 2;
    bool selected = false;

    virtual ~Objects() = default;
    virtual std::unique_ptr<Objects> clone() const = 0;
    virtual void draw(QPainter& painter) = 0;
    virtual void setEnd(int x2, int y2) = 0;
    virtual bool contains(int px, int py) const = 0;
    virtual void move(int dx, int dy) = 0;
    bool isOnResizeHandle(int px, int py) const;
    virtual QRect getBoundingBox() const = 0;
    virtual std::string toSVG() const = 0;

};

#endif // OBJECTS_H
