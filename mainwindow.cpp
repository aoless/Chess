#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QPixmap(":/dark.jpg")));
    board = new Board();
    board->drawChessBoard(scene);
    board->addPiecesToBoard(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board;
}
