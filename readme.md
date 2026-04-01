# MicroVectorEditor

MicroVectorEditor is vector graphics application developed. It features a robust object-oriented architecture for creating and manipulating geometric data in scalable formats.

##  Design Decisions

### 1. Object Hierarchy
The core architecture is built upon a base `Objects` class from which all shapes (Rectangle, Circle, Hexagon, RoundedRectangle, etc.) inherit.

* **Abstraction**: The `Canvas` treats all shapes as `std::unique_ptr<Objects>`, allowing for a unified rendering and manipulation loop.
* **Extensibility**: New geometric types can be integrated by overriding virtual methods like `draw()`, `move()`, and `toSVG()` without modifying existing canvas logic.

### 2. State Management 

* **Snapshot Undo/Redo**: To ensure state integrity, the system utilizes a snapshot-based undo stack. Each significant change triggers a deep copy of the current shape vector, providing a reliable recovery point.
* **Deep Cloning**: The `clone()` method is implemented in every shape class to facilitate accurate state duplication for both the undo system and the persistent clipboard.

### 3. Native SVG Format

The application utilizes **Scalable Vector Graphics (SVG)** as its primary storage format.

* **Serialization**: Shapes are converted to XML-compliant strings (e.g., `<rect>`, `<polygon>`, `<polyline>`) during the save process.
* **Custom Parsing**: An integrated SVG parser reads files line-by-line, reconstructing C++ object instances from XML attributes like `stroke`, `fill`, and `points`.

---

##  Compilation and Run Instructions

### Prerequisites

* **Qt 6.x** Framework (Widgets module required).
* **CMake 3.16** or higher.
* **C++17** compatible compiler (GCC, Clang, or MSVC).

### Build Workflow

1. **Navigate to the project root**:
```bash
cd MicroVectorEditor

```


2. **Create a build directory**:
```bash
mkdir build && cd build
```

3. **Configure with CMake**:
```bash
cmake ..
```

4. **Compile the source**:
```bash
make 
```

5. **Run the application**:
```bash
./MicroVectorEditor # Mac: ./MicroVectorEditor.app/Contents/MacOS/MicroVectorEditor
```



---

##  Edge Cases and Error Handling

| Scenario | Handling Strategy |
| --- | --- |
| **Unsaved Changes** | The `maybeSave()` gatekeeper intercepts "New", "Open", and "Close" actions, triggering a Save/Discard/Cancel dialog if the canvas contains data. |
| **Negative Dragging** | Drawing a shape "backward" (bottom-to-top) is handled by `QRect::normalized()`, ensuring selection logic and bounding boxes remain valid. |
| **Selection Visuals** | To prevent selection rectangles from inheriting shape fill colors, `painter.setBrush(Qt::NoBrush)` is explicitly set before drawing dashed outlines. |
| **Multi-Paste Logic** | The `paste()` operation clones objects from the clipboard rather than moving them, allowing the user to paste the same object repeatedly. |
| **Malformed SVG** | The parser skips unrecognized tags or invalid lines, allowing the application to load partial data rather than crashing on a single file error. |

---

