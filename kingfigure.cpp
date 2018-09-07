#include "kingfigure.h"
#include <QBrush>

KingFigure::KingFigure(figureColors type)
{
    color = type;
    this->setRect(0, 0, 100, 100);

    if (isWhite())
    {
        this->setBrush(QPixmap(":/figures images/king_white.png").scaledToHeight(100).scaledToWidth(100));
    }
    else
    {
        this->setBrush(QPixmap(":/figures images/king_black.png").scaledToHeight(100).scaledToWidth(100));
    }
}

bool KingFigure::moveIsValid()
{
    if (thereIsOtherPieceOnField())
        return false;

    bool goingToFarVerticaly = std::abs(previousPosition.second - int(this->y())) > 100;
    bool goingToFarHorizontaly = std::abs(previousPosition.first - int(this->x())) > 100;

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
    emit checkIfOtherFigureHasSamePosition(int(this->x()), int(this->y()));
    return occupancy;
}
