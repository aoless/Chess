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
};

#endif // KNIGHTFIGURE_H
