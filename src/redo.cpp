#include "Canvas.h"

void Canvas::redo() {
    if (redoStack.empty()) return;

    // Move current state to Undo stack before moving forward
    undoStack.push(createSnapshot());

    // Restore the state from the Redo stack
    CanvasState future = std::move(redoStack.top());
    redoStack.pop();

    this->shapes = std::move(future.shapes);
    this->currentStroke = future.stroke;
    this->currentFill = future.fill;
    this->currentStrokeWidth = future.width;

    update(); // Redraw the canvas
}
