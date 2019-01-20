#ifndef KNIGHTFIGURE_H
#define KNIGHTFIGURE_H

#include "abstractfigure.h"

class KnightFigure: virtual public AbstractFigure
{
public:
    explicit KnightFigure(figureColors type);
    bool dupa(int col, int row) { return moveIsValid(); }
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsOtherPieceOnField();
    vecOfPairs dangeredPositions();
    vecOfPairs possibleMoves();
};

#endif // KNIGHTFIGURE_H
