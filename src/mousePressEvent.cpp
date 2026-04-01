#include "Canvas.h"
#include"Rectangle.h"
#include"Circle.h"
#include"Line.h"
#include"Text.h"
#include"Hexagon.h"
#include"FreeHand.h"
#include"qinputdialog.h"
#include<QPaintEvent>
#include"roundedrectangle.h"

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        lastMousePos = event->pos();
        if (currentTool == Tool_Select) {
            if (selectedObject && selectedObject->isOnResizeHandle(event->pos().x(), event->pos().y())) {
                isResizing = true;
                isDrawing = false;
            }
            else {
                isResizing = false;
                isDrawing = false;
                selectedObject = nullptr;
                for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
                    (*it)->selected = false;
                    if (!selectedObject && (*it)->contains(event->pos().x(), event->pos().y())) {
                        selectedObject = it->get();
                        selectedObject->selected = true;
                    }
                }
            }
            update();
            return;
        }
        saveState();
        isDrawing = true;
        isResizing = false;
        if (currentTool == Tool_Rect) {
            auto rect = std::make_unique<Rectangle>();
            rect->x = startPoint.x();
            rect->y = startPoint.y();
            rect->width = 0;
            rect->height = 0;
            rect->stroke_width = currentStrokeWidth;
            rect->stroke = currentStroke.toStdString();
            rect->fill = currentFill.toStdString();
            shapes.push_back(std::move(rect));
        }else if (currentTool == Tool_RoundedRect){
            auto round_rect = std::make_unique<RoundedRectangle>();
            round_rect->x = startPoint.x();
            round_rect->y = startPoint.y();
            round_rect->width = 0;
            round_rect->height = 0;
            round_rect->stroke_width = currentStrokeWidth;
            round_rect->stroke = currentStroke.toStdString();
            round_rect->fill = currentFill.toStdString();
            shapes.push_back(std::move(round_rect));
        }else if (currentTool == Tool_Circle) {
            auto circle = std::make_unique<Circle>();
            circle->cx = startPoint.x();
            circle->cy = startPoint.y();
            circle->r = 0;
            circle->stroke_width = currentStrokeWidth;
            circle->stroke = currentStroke.toStdString();
            circle->fill = currentFill.toStdString();
            shapes.push_back(std::move(circle));
        }else if (currentTool == Tool_Line) {
            auto line = std::make_unique<Line>();
            line->x1 = startPoint.x();
            line->y1 = startPoint.y();
            line->x2 = startPoint.x();
            line->y2 = startPoint.y();
            line->stroke_width = currentStrokeWidth;
            line->stroke = currentStroke.toStdString();
            line->fill = currentFill.toStdString();
            shapes.push_back(std::move(line));
        }else if (currentTool == Tool_FreeHand) {
            auto fh = std::make_unique<FreeHand>();
            fh->stroke = currentStroke.toStdString();
            fh->stroke_width = currentStrokeWidth;
            fh->points.push_back(startPoint);
            shapes.push_back(std::move(fh));
        }else if (currentTool == Tool_Text) {
            bool ok;
            QString val = QInputDialog::getText(this, "Text Tool", "Enter text:", QLineEdit::Normal, "", &ok);
            if (ok && !val.isEmpty()) {
                auto txt = std::make_unique<Text>();
                txt->x = startPoint.x();
                txt->y = startPoint.y();
                txt->content = val;
                txt->font_size = currentFontSize;
                txt->stroke = currentStroke.toStdString();
                shapes.push_back(std::move(txt));
                update();
            }
        }else if (currentTool == Tool_Hexagon){
            auto hex = std::make_unique<Hexagon>();
            hex->cx = startPoint.x();
            hex->cy = startPoint.y();
            hex->stroke_width = currentStrokeWidth;
            hex->r = 0;
            hex->stroke = currentStroke.toStdString();
            hex->fill = currentFill.toStdString();
            shapes.push_back(std::move(hex));
        }
    }
}
