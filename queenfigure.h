#ifndef QUEENFIGURE_H
#define QUEENFIGURE_H

#include "abstractfigure.h"

class QueenFigure: virtual public AbstractFigure
{
private:
    bool beggining = true;
public:
    explicit QueenFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
};
#endif // QUEENFIGURE_H
