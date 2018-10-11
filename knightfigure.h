#ifndef KNIGHTFIGURE_H
#define KNIGHTFIGURE_H

#include "abstractfigure.h"

class KnightFigure: virtual public AbstractFigure
{
public:
    explicit KnightFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsOtherPieceOnField();
    vecOfPairs dangeredPositions();
};

#endif // KNIGHTFIGURE_H
