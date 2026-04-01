#ifndef CANVAS_H
#define CANVAS_H
#include<QWidget>
#include"Objects.h"
#include<QPainter>
#include<stack>

struct CanvasState {
    std::vector<std::unique_ptr<Objects>> shapes;
    QString stroke;
    QString fill;
    int width;
    int fontSize;
};

class Canvas : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public:
    explicit Canvas(QWidget *parent = nullptr) : QWidget(parent) {}

    int currentFontSize = 12;
    QString currentStroke = "black";
    QString currentFill = "transparent";
    int currentStrokeWidth = 2;
    QPoint startPoint;

    bool isDrawing;
    bool isResizing = false;

    std::vector<std::unique_ptr<Objects>> shapes;

    enum Tool { Tool_Rect = 1, Tool_RoundedRect, Tool_Circle, Tool_Line, Tool_Hexagon, Tool_Text, Tool_FreeHand, Tool_Select};
    Tool currentTool = Tool_Rect;

    void paintEvent(QPaintEvent *event) override;

    void undo();
    void redo();
    void saveState();

    Objects* selectedObject = nullptr;
    void cut();
    void copy();
    void paste();

    CanvasState createSnapshot();

    void saveToSVG(const QString &fileName);

private:
    QPoint lastMousePos;
    std::vector<std::unique_ptr<Objects>> cloneShapes(const std::vector<std::unique_ptr<Objects>>& source);

    std::stack<CanvasState> undoStack;
    std::stack<CanvasState> redoStack;
    std::unique_ptr<Objects> clipboard;
};
#endif // CANVAS_H
