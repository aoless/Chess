#ifndef BISHOPFIGURE_H
#define BISHOPFIGURE_H

#include "abstractfigure.h"

class BishopFigure : virtual public AbstractFigure
{
public:
    explicit BishopFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsOtherPieceOnField();
    bool isThereAnythingOnMyWay();

signals:

public slots:
};

#endif // BISHOPFIGURE_H
