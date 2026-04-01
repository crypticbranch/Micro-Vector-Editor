#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <qcolordialog.h>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include<QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle("Micro-Vector Editor");
    resize(800, 600);

    // Create the blank drawing area
    canvas = new Canvas(this);
    canvas->setStyleSheet("background-color: white;"); // Placeholder for canvas [cite: 54]
    setCentralWidget(canvas);

    setupMenus();
    setupToolBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::maybeSave() {
    if (canvas->shapes.empty()) {
        return true; // Nothing to save, proceed
    }
    auto reply = QMessageBox::question(this, "Unsaved Changes",
                                       "Do you want to save changes?",
                                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (reply == QMessageBox::Save) {
        if (currentOpenedFilePath.isEmpty()) {
            currentOpenedFilePath = QFileDialog::getSaveFileName(this, "Save Drawing", "", "SVG Files (*.svg)");
        }
        if (!currentOpenedFilePath.isEmpty()) {
            canvas->saveToSVG(currentOpenedFilePath);
            return true; // Saved successfully
        }
        return false; // User cancelled the File Dialog
    }
    if (reply == QMessageBox::Cancel) {
        return false; // User wants to stay in the current drawing
    }

    return true; // User chose 'Discard', so we can proceed
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (maybeSave()) {
        event->accept(); // Close the application
    } else {
        event->ignore(); // Keep the application open
    }
}
