#ifndef KNIGHTFIGURE_H
#define KNIGHTFIGURE_H

#include "abstractfigure.h"

class KnightFigure: virtual public AbstractFigure
{
private:
    bool beggining = true;
public:
    explicit KnightFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
};

#endif // KNIGHTFIGURE_H
