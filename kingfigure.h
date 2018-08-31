#ifndef KINGFIGURE_H
#define KINGFIGURE_H

#include "abstractfigure.h"

class KingFigure: virtual public AbstractFigure
{
public:
    explicit KingFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsNoOtherPieceOnField();
    bool isThereAnythingOnMyWay();
};

#endif // KINGFIGURE_H
