#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QRect>
#include <array>
#include "field.h"
#include "abstractfigure.h"
#include "pawnfigure.h"

using squareMatrix = std::array<std::array<Field*, 8>, 8>;

class Board
{
private:
    squareMatrix fields;
    PawnFigure *pawn;
public:
    Board();
    ~Board();
    QGraphicsRectItem* getSingleSquare(int row, int col);
    Field* getField(int row, int col);
    void drawChessBoard(QGraphicsScene *scene);
    void addPiecesToBoard(QGraphicsScene *scene);
};

#endif // BOARD_H
