#ifndef KNIGHTFIGURE_H
#define KNIGHTFIGURE_H

#include "abstractfigure.h"

class KnightFigure: virtual public AbstractFigure
{
public:
    explicit KnightFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsNoOtherPieceOnField();
    bool isThereAnythingOnMyWay();
};

#endif // KNIGHTFIGURE_H
