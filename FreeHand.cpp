#include "FreeHand.h"

void FreeHand:: draw(QPainter& painter)  {
    if (points.size() < 2) return;

    QPen pen(QColor(QString::fromStdString(stroke)), stroke_width);
    painter.setPen(pen);

    for (size_t i = 0; i < points.size() - 1; ++i) {
        painter.drawLine(points[i], points[i+1]);
    }

    if (selected) {
        // Draw a simple bounding box for selection feedback
        QRect rect = QRect(points[0], points[0]);
        for (const auto& p : points) {
            rect = rect.united(QRect(p, p));
        }

        painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter.drawRect(rect.adjusted(-3, -3, 3, 3));
    }

}

void FreeHand::setEnd(int x2, int y2){
    points.push_back(QPoint(x2, y2)); // Add new points as mouse moves
}

std::unique_ptr<Objects> FreeHand::clone() const  { return std::make_unique<FreeHand>(*this); }

bool FreeHand::contains(int px, int py) const {
    for (const auto& p : points) {
        if (std::abs(p.x() - px) < 10 && std::abs(p.y() - py) < 10) return true;
    }
    return false;
}

QRect FreeHand::getBoundingBox() const  {
    if (points.empty()) return QRect();
    QRect rect(points[0], points[0]);
    for(const auto& p : points) rect = rect.united(QRect(p, p));
    return rect;
}

void FreeHand::move(int dx, int dy)  {
    for (auto& p : points) {
        p.setX(p.x() + dx);
        p.setY(p.y() + dy);
    }
}

void FreeHand::resize(int dx, int dy) { /* Not implemented */ }

std::string FreeHand::toSVG() const {
    if (points.empty()) return "";

    std::string pointsString = "";
    for (const auto& p : points) {
        // Convert the vector of QPoints into the SVG points string
        pointsString += std::to_string(p.x()) + "," + std::to_string(p.y()) + " ";
    }

    // Polyline is used for open paths like sketches
    return "<polyline points=\"" + pointsString +
           "\" stroke=\"" + stroke +
           "\" fill=\"none\" " + // Free-hand usually shouldn't have fill
           "stroke-width=\"" + std::to_string(stroke_width) +
           "\" stroke-linecap=\"round\" stroke-linejoin=\"round\" />\n";
}
