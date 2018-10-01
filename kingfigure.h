#ifndef KINGFIGURE_H
#define KINGFIGURE_H

#include "abstractfigure.h"
#include <QString>

class KingFigure: virtual public AbstractFigure
{
private:
    bool already_moved = false;
public:
    explicit KingFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsOtherPieceOnField();
    bool isThereAnythingOnMyWay();
};

#endif // KINGFIGURE_H
