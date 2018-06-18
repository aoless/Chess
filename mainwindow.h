#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "board.h"
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QGraphicsScene *scene;
    Board *board;
    QLabel *coordinates;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connecter();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
