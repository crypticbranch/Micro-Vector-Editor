#include "Canvas.h"
#include <QPaintEvent>

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing && !shapes.empty() && currentTool != Tool_Select) {
        shapes.back()->setEnd(event->pos().x(), event->pos().y());
    } else if (currentTool == Tool_Select && selectedObject) {
        int dx = event->pos().x() - lastMousePos.x();
        int dy = event->pos().y() - lastMousePos.y();

        if (isResizing) {
            selectedObject->resize(dx, dy);
        } else {
            selectedObject->move(dx, dy);
        }
        lastMousePos = event->pos();
    }
    update();
}
