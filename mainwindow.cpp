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
    scene->setSceneRect(0, 0, 800, 800);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QPixmap(":/dark.jpg")));
    board = new Board();
    board->drawChessBoard(scene);
    board->createFiguresAndAddPiecesToBoard(scene);
    connecter();
}

void MainWindow::connecter()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            connect(board->getField(i, j), SIGNAL(showCoordinates(QString)),
                ui->label, SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board;
}
