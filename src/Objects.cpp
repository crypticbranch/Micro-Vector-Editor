#include "Objects.h"

bool Objects::isOnResizeHandle(int px, int py) const{
    QRect rect = getBoundingBox();
    QRect handle(rect.right() - 5, rect.bottom() - 5, 10, 10);
    return handle.contains(px, py);
}
