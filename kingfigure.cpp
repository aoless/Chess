#include "kingfigure.h"
#include <QBrush>

KingFigure::KingFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
        setBrush(QPixmap(":/figures images/king_white.png").scaledToHeight(100).scaledToWidth(100));
    else
        setBrush(QPixmap(":/figures images/king_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool KingFigure::moveIsValid()
{
    if (thereIsOtherPieceOnField())
        return false;

    bool goingToFarVerticaly = std::abs(previousPosition.second - int(y())) > 100;
    bool goingToFarHorizontaly = std::abs(previousPosition.first - int(x())) > 100;

    if (goingToFarVerticaly || goingToFarHorizontaly)
        return false;

    return true;
}

bool KingFigure::isItPossibleToBeat()
{
    return false;
}

bool KingFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(int(x()), int(y()), color);
    return occupancy;
}
