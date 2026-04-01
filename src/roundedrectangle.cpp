#include "roundedrectangle.h"

RoundedRectangle::RoundedRectangle(int x1, int y1, int rx, int ry)
{
    x = x1;
    y = y1;
    this->rx = rx;
    this->ry = ry;
}

void RoundedRectangle:: draw(QPainter& painter){
    QPen pen(QColor(QString::fromStdString(stroke)), stroke_width);
    painter.setPen(pen);

    if (fill == "none" || fill == "transparent") {
        painter.setBrush(Qt::NoBrush);
    } else {
        painter.setBrush(QColor(QString::fromStdString(fill)));
    }

    QRect rect = getBoundingBox();
    painter.drawRoundedRect(rect, rx, ry);

    if (selected) {
        QPen dashPen(Qt::blue, 1, Qt::DashLine);
        painter.setPen(dashPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(x - 3, y - 3, width + 6, height + 6);

        painter.setBrush(Qt::white);
        painter.setPen(Qt::blue);
        // Draw the small handle square at the bottom right
        painter.drawRect(rect.right() - 4, rect.bottom() - 4, 8, 8);
    }
}

std::unique_ptr<Objects> RoundedRectangle ::clone() const { return std::make_unique<RoundedRectangle>(*this); }

std::string RoundedRectangle ::toSVG() const  {
    QRect rect = getBoundingBox();
    return "<rect x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) +
           "\" width=\"" + std::to_string(rect.width()) + "\" height=\"" + std::to_string(rect.height()) +
           "\" rx=\"" + std::to_string(rx) +
           "\" ry=\"" + std::to_string(ry) +
           "\" stroke=\"" + stroke + "\" fill=\"" + fill +
           "\" stroke-width=\"" + std::to_string(stroke_width) + "\" />\n";
}
