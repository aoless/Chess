#ifndef PAWNFIGURE_H
#define PAWNFIGURE_H

#include "abstractfigure.h"

class PawnFigure : virtual public AbstractFigure
{
private:
    bool beggining = true;
public:
    explicit PawnFigure(figureColors type);
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool isItBegginingOfGame();
    bool thereIsOtherPieceOnField();
    vecOfPairs dangeredPositions();
};

#endif // PAWNFIGURE_H
