#include "mainwindow.h"
#include<qcolordialog.h>
#include<QInputDialog>
#include<QStatusBar>
#include "Objects.h"
#include "Text.h"

void MainWindow::setupToolBar() {
    QToolBar *toolbar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, toolbar);

    // Grouping tools so only one is active at a time
    QActionGroup *group = new QActionGroup(this);

    QStringList tools = {"Rectangle", "rounded rectangle", "Circle", "Line", "Hexagon", "Text","FreeHand", "Select"};
    for (int i = 0; i < tools.size(); ++i) {
        QAction *action = toolbar->addAction(tools[i]);
        action->setCheckable(true);
        group->addAction(action);
        connect(action, &QAction::triggered, [this, i]() {
            canvas->currentTool = static_cast<Canvas::Tool>(i + 1);
        });
    }

    toolbar->addSeparator();

    QAction *strokeAction = toolbar->addAction("Stroke Color");
    connect(strokeAction, &QAction::triggered, [this]() {
        QColor color = QColorDialog::getColor(Qt::black, this, "Select Stroke Color");
        if (color.isValid()) {
            if (canvas->selectedObject) {
                canvas->saveState();
                canvas->selectedObject->stroke = color.name().toStdString();
                canvas->currentStroke = color.name();
                canvas->update();
            } else {
                canvas->currentStroke = color.name();
            }
        }
    });

    QAction *fillAction = toolbar->addAction("Fill Color");
    connect(fillAction, &QAction::triggered, [this]() {
        QColor color = QColorDialog::getColor(Qt::white, this, "Select Fill Color");
        if (color.isValid()) {
            if (canvas->selectedObject) {
                canvas->saveState();
                canvas->selectedObject->fill = color.name().toStdString();
                canvas->update(); // Forces immediate redraw
            } else {
                canvas->currentFill = color.name();
            }
        }
    });

    QAction *widthAction = toolbar->addAction("Stroke Width");
    connect(widthAction, &QAction::triggered, [this]() {
        bool ok;
        int newSize = QInputDialog::getInt(this, "Set Size", "Value:",
                                           canvas->currentStrokeWidth, 1, 100, 1, &ok);
        if (ok) {
            if (canvas->selectedObject) {
                canvas->saveState(); // Save before modifying

                // Try to see if it's a Text object
                Text* textObj = dynamic_cast<Text*>(canvas->selectedObject);

                if (textObj) {
                    // If it's text, update font_size
                    textObj->font_size = newSize;
                } else {
                    // If it's a shape, update stroke_width
                    canvas->selectedObject->stroke_width = newSize;
                }
                canvas->update(); // Redraw immediately
            }
            // Update the default values for the next item you draw
            canvas->currentStrokeWidth = newSize;
            canvas->currentFontSize = newSize;
        }
    });

    QAction *resetAction = toolbar->addAction("Reset Colors");
    connect(resetAction, &QAction::triggered, [this]() {
        canvas->currentStroke = "black";
        canvas->currentFill = "none";
        canvas->currentStrokeWidth = 2; // Also reset width to default
        if (canvas->selectedObject) {
            canvas->saveState(); // Save for undo before changing colors

            canvas->selectedObject->stroke = "black";
            canvas->selectedObject->fill = "none";
            canvas->selectedObject->stroke_width = 2;

            canvas->update(); // Redraw immediately
        }
        statusBar()->showMessage("Colors reset to default (Transparent Fill)", 2000);
    });
}
