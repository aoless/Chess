#ifndef BISHOPFIGURE_H
#define BISHOPFIGURE_H

#include "abstractfigure.h"

class BishopFigure : virtual public AbstractFigure
{
public:
    explicit BishopFigure(figureColors type);
    bool dupa(int col, int row) { return moveIsValid(); }
    bool moveIsValid();
    bool isItPossibleToBeat();
    bool thereIsOtherPieceOnField();
    bool isThereAnythingOnMyWay();
    vecOfPairs dangeredPositions();
    vecOfPairs possibleMoves();

signals:

public slots:
};

#endif // BISHOPFIGURE_H
