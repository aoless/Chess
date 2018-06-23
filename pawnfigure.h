#ifndef PAWNFIGURE_H
#define PAWNFIGURE_H

#include "abstractfigure.h"

class PawnFigure : virtual public AbstractFigure
{
public:
    enum color { white, black };
    PawnFigure(color type);
};

#endif // PAWNFIGURE_H
