#include"Circle.h"

void Circle:: draw(QPainter& painter){
    QPen pen(QColor(QString::fromStdString(stroke)), stroke_width);
    painter.setPen(pen);
    if (fill == "none" || fill == "transparent") {
        painter.setBrush(Qt::NoBrush);
    } else {
        painter.setBrush(QColor(QString::fromStdString(fill)));
    }
    painter.drawEllipse(cx-r, cy-r, 2*r, 2*r);

    if (selected) {
        QPen dashPen(Qt::blue, 1, Qt::DashLine);
        painter.setPen(dashPen);
        painter.setBrush(Qt::NoBrush);
        // Draw dashed square bounding the circle
        painter.drawRect(cx - r - 3, cy - r - 3, (2 * r) + 6, (2 * r) + 6);

        QRect rect = getBoundingBox();
        painter.setBrush(Qt::white);
        painter.setPen(Qt::blue);
        // Draw the small handle square at the bottom right
        painter.drawRect(rect.right() - 4, rect.bottom() - 4, 8, 8);
    }
}

void Circle:: setEnd(int x2, int y2) {
    // Calculate radius using the distance formula
    // r = sqrt((x2-cx)^2 + (y2-cy)^2)
    double dx = x2 - this->cx;
    double dy = y2 - this->cy;
    this->r = static_cast<int>(std::sqrt(dx * dx + dy * dy));
}

std::unique_ptr<Objects> Circle::clone() const { return std::make_unique<Circle>(*this); }

bool Circle::contains(int px, int py) const {
    int x = px - cx;
    int y = py - cy;
    int pr = static_cast<int>(std::sqrt(x * x + y * y));
    return (pr <= r);
}

QRect Circle:: getBoundingBox() const{
    return QRect(cx - r, cy - r, 2 * r, 2 * r);
}

void Circle:: move(int dx, int dy) {
    this->cx += dx;
    this->cy += dy;
}

void Circle:: resize(int dx, int dy){
    // Increase radius based on horizontal movement
    this->r = std::max(5, r + dx);
}

std::string Circle:: toSVG() const {
    return "<circle cx=\"" + std::to_string(cx) + "\" cy=\"" + std::to_string(cy) +
           "\" r=\"" + std::to_string(r) +
           "\" stroke=\"" + stroke + "\" fill=\"" + fill +
           "\" stroke-width=\"" + std::to_string(stroke_width) + "\" />\n";
}
