#include"Canvas.h"
#include<QPaintEvent>
#include <QFile>
#include <QTextStream>

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    for (const auto& shape : shapes) {
        shape->draw(painter);
    }
}

void Canvas::saveState() {
    undoStack.push(createSnapshot());

    while (!redoStack.empty()) redoStack.pop();
}

std::vector<std::unique_ptr<Objects>> Canvas::cloneShapes(const std::vector<std::unique_ptr<Objects>>& source) {
    std::vector<std::unique_ptr<Objects>> copy;
    for (const auto& obj : source) {
        copy.push_back(obj->clone());
    }
    return copy;
}

void Canvas::copy() {
    if (selectedObject) {
        // Create a deep copy using the clone()
        clipboard = selectedObject->clone();
    }
}

void Canvas::cut() {
    if (selectedObject) {
        saveState(); // Save to undo stack before deleting
        copy();      // Copy the object to clipboard first

        // Find the selected object in the vector and erase it
        for (auto it = shapes.begin(); it != shapes.end(); ++it) {
            if (it->get() == selectedObject) {
                shapes.erase(it);
                break;
            }
        }
        selectedObject = nullptr;
        update();
    }
}

void Canvas::paste() {
    if (clipboard) {
        saveState(); // Save to undo stack

        // Clone the clipboard so the clipboard remains intact for multiple pastes
        auto pastedShape = clipboard->clone();

        // Offset the new shape so the user can see it
        pastedShape->move(20, 20);

        // Deselect the old one and select the new pasted one
        if (selectedObject) selectedObject->selected = false;
        selectedObject = pastedShape.get();
        selectedObject->selected = true;

        clipboard = selectedObject->clone();

        shapes.push_back(std::move(pastedShape));
        update();
    }
}

CanvasState Canvas::createSnapshot() {
    CanvasState state;
    state.shapes = cloneShapes(shapes);
    state.stroke = currentStroke;
    state.fill = currentFill;
    state.width = currentStrokeWidth;
    return state;
}

void Canvas::saveToSVG(const QString &fileName) {
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);

    // Write SVG Header
    out << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
    out << "<svg width=\"" << width() << "\" height=\"" << height()
        << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    // Iterate through shapes and export them
    for (const auto& shape : shapes) {
        out << QString::fromStdString(shape->toSVG());
    }

    // Close SVG tag
    out << "</svg>\n";
    file.close();
}

