#include "board.h"

Board::Board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fields[i][j] = new Field(i, j);
        }
    }
    pawn = new PawnFigure();
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
    scene->addItem(pawn);

}
