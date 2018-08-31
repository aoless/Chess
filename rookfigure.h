#ifndef ROOKFIGURE_H
#define ROOKFIGURE_H

#include "abstractfigure.h"

class RookFigure : virtual public AbstractFigure
{
public:
    explicit RookFigure(figureColors color);
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsNoOtherPieceOnField();
    bool isThereAnythingOnMyWay();

signals:

public slots:
};

#endif // ROOKFIGURE_H
