#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QActionGroup>
#include "Canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupMenus();
    void setupToolBar();
    Ui::MainWindow *ui;
    Canvas *canvas;
    QString currentOpenedFilePath = "";
    bool maybeSave();
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
