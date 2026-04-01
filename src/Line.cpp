#include "Line.h"

void Line ::draw(QPainter& painter) {
    painter.setPen(QPen(QColor(QString::fromStdString(stroke)), stroke_width));
    painter.drawLine(x1, y1, x2, y2);

    if (selected) {
        QPen dashPen(Qt::blue, 1, Qt::DashLine);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(dashPen);
        int minX = std::min(x1, x2);
        int maxX = std::max(x1, x2);
        int minY = std::min(y1, y2);
        int maxY = std::max(y1, y2);
        painter.drawRect(minX - 5, minY - 5, (maxX - minX) + 10, (maxY - minY) + 10);

        QRect rect = getBoundingBox();
        painter.setBrush(Qt::white);
        painter.setPen(Qt::blue);
        // Draw the small handle square at the bottom right
        painter.drawRect(rect.right() - 4, rect.bottom() - 4, 8, 8);
    }
}

void Line :: setEnd(int x2, int y2) {
    this->x2 = x2;
    this->y2 = y2;
}

std::unique_ptr<Objects> Line:: clone() const { return std::make_unique<Line>(*this); }

bool Line :: contains(int px, int py) const {
    // Simple bounding box check for the line
    int minX = std::min(x1, x2) - 5;
    int maxX = std::max(x1, x2) + 5;
    int minY = std::min(y1, y2) - 5;
    int maxY = std::max(y1, y2) + 5;
    return (px >= minX && px <= maxX && py >= minY && py <= maxY);
}

QRect Line::getBoundingBox() const  {
    int minX = std::min(x1, x2);
    int minY = std::min(y1, y2);
    return QRect(minX, minY, std::abs(x2 - x1), std::abs(y2 - y1));
}

void Line:: move(int dx, int dy){
    this->x1 += dx;
    this->y1 += dy;
    this->x2 += dx;
    this->y2 += dy;
}

void Line::resize(int dx, int dy)  {
    // Resizing a line updates the second endpoint
    this->x2 += dx;
    this->y2 += dy;
}

std::string Line::toSVG() const  {
    return "<line x1=\"" + std::to_string(x1) + "\" y1=\"" + std::to_string(y1) +
           "\" x2=\"" + std::to_string(x2) + "\" y2=\"" + std::to_string(y2) +
           "\" stroke=\"" + stroke +
           "\" stroke-width=\"" + std::to_string(stroke_width) + "\" />\n";
}
