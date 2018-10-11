#ifndef QUEENFIGURE_H
#define QUEENFIGURE_H

#include "abstractfigure.h"

class QueenFigure: virtual public AbstractFigure
{
public:
    explicit QueenFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsOtherPieceOnField();
    bool isThereAnythingOnMyWay();
    vecOfPairs dangeredPositions();
};
#endif // QUEENFIGURE_H
