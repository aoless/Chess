#include "bishopfigure.h"
#include <QBrush>
#include <cmath>

BishopFigure::BishopFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
        setBrush(QPixmap(":/figures images/bishop_white.png").scaledToHeight(100).scaledToWidth(100));
    else
        setBrush(QPixmap(":/figures images/bishop_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool BishopFigure::moveIsValid()
{
    if (isThereAnythingOnMyWay() || thereIsOtherPieceOnField())
        return false;

    int rowOffset = int(std::abs(y() - previousPosition.second));

    if (rowOffset == int(std::abs(x() - previousPosition.first)))
        return true;

    return false;
}

bool BishopFigure::isItPossibleToBeat()
{
    return false;
}

bool BishopFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(int(x()), int(y()), color);
    return occupancy;
}

bool BishopFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - int(y()) > 0;
    bool goingRight = previousPosition.first - int(x()) < 0;

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

    for (col = previousPosition.first, row = previousPosition.second; col != int(x()) && row != int(y());
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row, color);
        if (blocked_by_piece)
            return true;
    }
    return false;
}
