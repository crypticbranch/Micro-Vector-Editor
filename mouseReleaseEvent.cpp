#include"Canvas.h"
#include"QPaintEvent"

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDrawing = false;
        isResizing = false;
    }
}
