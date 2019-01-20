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
    bool dupa(int col, int row);
    bool isItPossibleToBeat();
    bool thereIsOtherPieceOnField();
    bool isThereAnythingOnMyWay();
    vecOfPairs dangeredPositions();
    vecOfPairs possibleMoves();
};

#endif // KINGFIGURE_H
