#include "knightfigure.h"
#include <QBrush>

KnightFigure::KnightFigure(figureColors type)
{
    color = type;
    this->setRect(0, 0, 100, 100);

    if (isWhite())
        this->setBrush(QPixmap(":/figures images/knight_white.png").scaledToHeight(100).scaledToWidth(100));
    else
        this->setBrush(QPixmap(":/figures images/knight_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool KnightFigure::moveIsValid()
{
    if (thereIsOtherPieceOnField())
        return false;

    int colJump = std::abs(previousPosition.second - int(this->y()));
    int rowJump = std::abs(previousPosition.first - int(this->x()));

    if (colJump == 100 && rowJump == 200)
        return true;
    else if (colJump == 200 && rowJump == 100)
        return true;
    else
        return false;
}

bool KnightFigure::isItPossibleToBeat()
{
    return false;
}

bool KnightFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(int(this->x()), int(this->y()));
    return occupancy;
}
