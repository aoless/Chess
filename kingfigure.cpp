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
    if (thereIsOtherPieceOnField() && !isItPossibleToBeat())
        return false;

    if(isItPossibleToBeat())
        emit beatFigure(horizontalPos(), verticalPos(), color);

    bool goingToFarVerticaly = std::abs(previousPosition.second - verticalPos()) > 100;
    bool goingToFarHorizontaly = std::abs(previousPosition.first - horizontalPos()) > 100;

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
    emit checkIfOtherFigureHasSamePosition(horizontalPos(), verticalPos(), color);
    return occupancy;
}
