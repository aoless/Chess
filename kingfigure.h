#ifndef KINGFIGURE_H
#define KINGFIGURE_H

#include "abstractfigure.h"

class KingFigure: virtual public AbstractFigure
{
private:
    bool beggining = true;
public:
    explicit KingFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
};

#endif // KINGFIGURE_H
