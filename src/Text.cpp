#include "Text.h"

void Text::draw(QPainter& painter)  {
    QFont font = painter.font();
    font.setPointSize(this->font_size);
    painter.setFont(font);
    painter.setPen(QColor(QString::fromStdString(stroke)));
    painter.drawText(x, y, content);

    if (selected) {
        QFontMetrics fm(font);
        painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(x, y - fm.ascent(), fm.horizontalAdvance(content), fm.height());

        QRect rect = getBoundingBox();
        painter.setBrush(Qt::white);
        painter.setPen(Qt::blue);
        // Draw the small handle square at the bottom right
        painter.drawRect(rect.right() - 4, rect.bottom() - 4, 8, 8);
    }
}

void Text::setEnd(int x2, int y2) { /* Text doesn't resize via drag */ }

std::unique_ptr<Objects> Text::clone() const  { return std::make_unique<Text>(*this); }

bool Text::contains(int px, int py) const  {
    // Simple hit-test based on approximate text area
    return (std::abs(px - x) < 50 && std::abs(py - y) < 20);
}

QRect Text::getBoundingBox() const {
    // Approximate bounding box based on typical text metrics
    QFont font;
    font.setPointSize(font_size);
    QFontMetrics fm(font);
    return QRect(x, y - fm.ascent(), fm.horizontalAdvance(content), fm.height());
}

void Text::move(int dx, int dy)  {
    x += dx; y += dy;
}

void Text::resize(int dx, int dy) {
    // For text, we can use resize to change font size
    this->font_size = std::max(5, font_size + dx);
}

std::string Text::toSVG() const {
    return "<text x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) +
           "\" font-size=\"" + std::to_string(font_size) + "\" fill=\"" + stroke + "\">" +
           content.toStdString() + "</text>\n";
}
