#include "Hexagon.h"
#include <cmath>
#include <QPolygonF>

void Hexagon::draw(QPainter& painter) {
    QPolygonF points;
    for (int i = 0; i < 6; ++i) {
        double angle = i * M_PI / 3.0;
        double px = cx + r * std::cos(angle);
        double py = cy + r * std::sin(angle);
        points << QPointF(px, py);
    }

    // Set Pen and Brush from attributes
    painter.setPen(QPen(QColor(QString::fromStdString(stroke)), stroke_width));
    if (fill != "none" && fill != "transparent") {
        painter.setBrush(QColor(QString::fromStdString(fill)));
    } else {
        painter.setBrush(Qt::NoBrush);
    }

    painter.drawPolygon(points);

    if (selected) {
        QPen dashPen(Qt::blue, 1, Qt::DashLine);
        painter.setPen(dashPen);
        painter.setBrush(Qt::NoBrush);
        // Draw a bounding square around the hexagon
        painter.drawRect(cx - r - 3, cy - r - 3, (2 * r) + 6, (2 * r) + 6);

        QRect rect = getBoundingBox();
        painter.setBrush(Qt::white);
        painter.setPen(Qt::blue);
        // Draw the small handle square at the bottom right
        painter.drawRect(rect.right() - 4, rect.bottom() - 4, 8, 8);
    }
}

void Hexagon::setEnd(int x2, int y2) {
    // Distance formula for radius
    double dx = x2 - cx;
    double dy = y2 - cy;
    r = static_cast<int>(std::sqrt(dx * dx + dy * dy));
}

std::unique_ptr<Objects> Hexagon::clone() const  {
    return std::make_unique<Hexagon>(*this);
}

bool Hexagon::contains(int px, int py) const  {
    double dx = px - cx;
    double dy = py - cy;
    double distance = std::sqrt(dx * dx + dy * dy);

    return distance <= r;
}

QRect Hexagon::getBoundingBox() const {
    return QRect(cx - r, cy - r, 2 * r, 2 * r);
}

void Hexagon::move(int dx, int dy) {
    this->cx += dx;
    this->cy += dy;
}

void Hexagon::resize(int dx, int dy) {
    this->r = std::max(5, r + dx);
}

std::string Hexagon::toSVG() const {
    std::string pointsString = "";
    for (int i = 0; i < 6; ++i) {
        // Calculate each vertex of the regular hexagon
        double angle_deg = 60 * i;
        double angle_rad = M_PI / 180 * angle_deg;
        int px = cx + r * cos(angle_rad);
        int py = cy + r * sin(angle_rad);

        pointsString += std::to_string(px) + "," + std::to_string(py) + " ";
    }

    return "<polygon points=\"" + pointsString +
           "\" stroke=\"" + stroke +
           "\" fill=\"" + fill +
           "\" stroke-width=\"" + std::to_string(stroke_width) + "\" />\n";
}
