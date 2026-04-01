#include "Rectangle.h"

void Rectangle:: draw(QPainter& painter){
    QPen pen(QColor(QString::fromStdString(stroke)), stroke_width);
    painter.setPen(pen);

    if (fill == "none" || fill == "transparent") {
        painter.setBrush(Qt::NoBrush);
    } else {
        painter.setBrush(QColor(QString::fromStdString(fill)));
    }

    painter.drawRect(x, y, width, height);

    if (selected) {
        QPen dashPen(Qt::blue, 1, Qt::DashLine);
        painter.setPen(dashPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(x - 3, y - 3, width + 6, height + 6);

        QRect rect = getBoundingBox();
        painter.setBrush(Qt::white);
        painter.setPen(Qt::blue);
        // Draw the small handle square at the bottom right
        painter.drawRect(rect.right() - 4, rect.bottom() - 4, 8, 8);
    }
}
void Rectangle :: setEnd(int x2, int y2) {
    this->width = x2 - this->x;
    this->height = y2 - this->y;
}

std::unique_ptr<Objects> Rectangle ::clone() const { return std::make_unique<Rectangle>(*this); }

bool Rectangle :: contains(int px, int py) const{
    // Normalizing coordinates for hit-testing
    int rx = width < 0 ? x + width : x;
    int ry = height < 0 ? y + height : y;
    int rw = std::abs(width);
    int rh = std::abs(height);
    return (px >= rx && px <= rx + rw && py >= ry && py <= ry + rh);
}

QRect Rectangle ::getBoundingBox() const  {
    return QRect(x, y, width, height).normalized();
}

void Rectangle :: move(int dx, int dy) {
    this->x += dx;
    this->y += dy;
}

void Rectangle :: resize(int dx, int dy)  {
    this->width += dx;
    this->height += dy;
}

std::string Rectangle ::toSVG() const  {
    return "<rect x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) +
           "\" width=\"" + std::to_string(width) + "\" height=\"" + std::to_string(height) +
           "\" stroke=\"" + stroke + "\" fill=\"" + fill +
           "\" stroke-width=\"" + std::to_string(stroke_width) + "\" />\n";
}
