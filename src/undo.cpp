#include "Canvas.h"

void Canvas::undo() {
    if (undoStack.empty()) return;

    // Save CURRENT state to redo before jumping back
    redoStack.push(createSnapshot());

    // Pop the previous state
    CanvasState previous = std::move(undoStack.top());
    undoStack.pop();

    // RESTORE EVERYTHING
    this->shapes = std::move(previous.shapes);
    this->currentStroke = previous.stroke;
    this->currentFill = previous.fill;
    this->currentStrokeWidth = previous.width;

    update();
}
