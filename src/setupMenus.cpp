#include "mainwindow.h"
#include<QMenuBar>
#include<QMenu>
#include<QMessageBox>
#include<QFileDialog>
#include<QStatusBar>
#include "svgparser.h"
#include<QApplication>

void MainWindow::setupMenus() {
    QMenu *fileMenu = menuBar()->addMenu("&File");

    QAction *newAct = fileMenu->addAction("New");
    connect(newAct, &QAction::triggered, [this]() {
        // 1. Check if there are shapes to save
        if (maybeSave()) {
            canvas->shapes.clear();
            canvas->selectedObject = nullptr;
            currentOpenedFilePath = "";
            canvas->update();
            statusBar()->showMessage("New Canvas Created", 2000);
        }
    });

    QAction *openAct = fileMenu->addAction("Open");
    connect(openAct, &QAction::triggered, [this]() {
        if (maybeSave()) {
            QString fileName = QFileDialog::getOpenFileName(this, "Open SVG", "", "SVG Files (*.svg)");
            if (!fileName.isEmpty()) {
                canvas->shapes = parseSVG(fileName.toStdString());
                currentOpenedFilePath = fileName;
                canvas->update();
            }
        }
    });

    QAction *saveAct = fileMenu->addAction("&Save");
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, [this]() {
        if (currentOpenedFilePath.isEmpty()) {
            // If no file is open, behave like "Save As"
            currentOpenedFilePath = QFileDialog::getSaveFileName(this, "Save Drawing", "", "SVG Files (*.svg)");
        }

        if (!currentOpenedFilePath.isEmpty()) {
            canvas->saveToSVG(currentOpenedFilePath);
            statusBar()->showMessage("Saved: " + currentOpenedFilePath, 2000);
        }
    });

    QAction *saveAction = fileMenu->addAction("Save As");
    connect(saveAction, &QAction::triggered, [this]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Drawing", "", "SVG Files (*.svg)");
        if (!fileName.isEmpty()) {
            canvas->saveToSVG(fileName);
        }
    });

    fileMenu->addSeparator();

    QAction *closeAction = fileMenu->addAction("&Close");
    connect(closeAction, &QAction::triggered, [this]() {
        this->close();
    });

    QMenu *editMenu = menuBar()->addMenu("&Edit");
    QAction *cutAct = editMenu->addAction("Cut");
    cutAct->setShortcut(QKeySequence::Cut);
    connect(cutAct, &QAction::triggered, canvas, &Canvas::cut);

    QAction *copyAct = editMenu->addAction("Copy");
    copyAct->setShortcut(QKeySequence::Copy);
    connect(copyAct, &QAction::triggered, canvas, &Canvas::copy);

    QAction *pasteAct = editMenu->addAction("Paste");
    pasteAct->setShortcut(QKeySequence::Paste);
    connect(pasteAct, &QAction::triggered, canvas, &Canvas::paste);

    QAction *undoAct = editMenu->addAction("Undo");
    undoAct->setShortcut(QKeySequence::Undo); // Standard Ctrl+Z
    connect(undoAct, &QAction::triggered, canvas, &Canvas::undo);

    QAction *redoAct = editMenu->addAction("Redo");
    redoAct->setShortcut(QKeySequence::Redo); // Standard Ctrl+Y or Ctrl+Shift+Z
    connect(redoAct, &QAction::triggered, canvas, &Canvas::redo);
}
