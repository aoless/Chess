#ifndef ROOKFIGURE_H
#define ROOKFIGURE_H

#include "abstractfigure.h"

class RookFigure : virtual public AbstractFigure
{
public:
    explicit RookFigure(figureColors color);
    bool dupa(int col, int row) { return moveIsValid(); }
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsOtherPieceOnField();
    bool isThereAnythingOnMyWay();
    vecOfPairs dangeredPositions();
};

#endif // ROOKFIGURE_H
