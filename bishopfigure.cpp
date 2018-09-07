#include "bishopfigure.h"
#include <QBrush>
#include <cmath>

BishopFigure::BishopFigure(figureColors type)
{
    color = type;
    this->setRect(0, 0, 100, 100);

    if (isWhite())
    {
        this->setBrush(QPixmap(":/figures images/bishop_white.png").scaledToHeight(100).scaledToWidth(100));
    }
    else
    {
       this->setBrush(QPixmap(":/figures images/bishop_black.png").scaledToHeight(100).scaledToWidth(100));
    }
}

bool BishopFigure::moveIsValid()
{
    if (isThereAnythingOnMyWay() || thereIsOtherPieceOnField())
        return false;

    int rowOffset = int(std::abs(this->y() - previousPosition.second));

    if (rowOffset == int(std::abs(this->x() - previousPosition.first)))
        return true;

    return false;
}

bool BishopFigure::isItPossibleToBeat()
{
    return false;
}

bool BishopFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(int(this->x()), int(this->y()));
    return occupancy;
}

bool BishopFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - int(this->y()) > 0;
    bool goingRight = previousPosition.first - int(this->x()) < 0;

    if (goingUp && goingRight)
    {
        colOffset = 100;
        rowOffset = -100;
    }
    else if (goingUp && !goingRight)
    {
        colOffset = -100;
        rowOffset = -100;
    }
    else if (!goingUp && goingRight)
    {
        colOffset = 100;
        rowOffset = 100;
    }
    else
    {
        colOffset = -100;
        rowOffset = 100;
    }

    for (col = previousPosition.first, row = previousPosition.second; col != int(this->x()) && row != int(this->y());
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row);
        if (blockedByPiece)
            return true;
    }
    return false;
}
