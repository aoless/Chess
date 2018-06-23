#include "board.h"
#include "mainwindow.h"

Board::Board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fields[i][j] = new Field(i, j);
        }
    }
    white_pawn = new PawnFigure(PawnFigure::white);
    black_pawn = new PawnFigure(PawnFigure::black);
}

Board::~Board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete fields[i][j];
}

QGraphicsRectItem * Board::getSingleSquare(int col, int row)
{
    return fields[col][row]->drawSquare();
}

Field *Board::getField(int row, int col)
{
    return fields[row][col];
}

void Board::drawChessBoard(QGraphicsScene *scene)
{
    qreal x = 0; qreal y = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scene->addItem(getSingleSquare(i, j));
            getSingleSquare(i, j)->setPos(x, y);
            x += 100;
        }
        y += 100;
        x = 0;
    }
}

void Board::addPiecesToBoard(QGraphicsScene *scene)
{
    scene->addItem(white_pawn);
    scene->addItem(black_pawn);
}

