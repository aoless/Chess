#ifndef PAWNFIGURE_H
#define PAWNFIGURE_H

#include "abstractfigure.h"

class PawnFigure : virtual public AbstractFigure
{
private:
    bool beggining = true;
public:
    explicit PawnFigure(figureColors type);
    bool dupa(int col, int row) { return moveIsValid(); }
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool isItBegginingOfGame();
    bool thereIsOtherPieceOnField();
    vecOfPairs dangeredPositions();
    vecOfPairs possibleMoves();
};

#endif // PAWNFIGURE_H
