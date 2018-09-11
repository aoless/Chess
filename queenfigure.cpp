#include "queenfigure.h"
#include <QBrush>

QueenFigure::QueenFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
        setBrush(QPixmap(":/figures images/queen_white.png").scaledToHeight(100).scaledToWidth(100));
    else
        setBrush(QPixmap(":/figures images/queen_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool QueenFigure::moveIsValid()
{
    if (isThereAnythingOnMyWay() || thereIsOtherPieceOnField())
        return false;

    return true;
}

bool QueenFigure::isItPossibleToBeat()
{
    return false;
}

bool QueenFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(int(x()), int(y()), color);
    return occupancy;
}

bool QueenFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - int(y()) > 0;
    bool goingDown = previousPosition.second - int(y()) < 0;
    bool goingRight = previousPosition.first - int(x()) < 0;
    bool goingLeft = previousPosition.first - int(x()) > 0;

    if (goingUp && goingRight)
    {
        colOffset = 100; rowOffset = -100;
    }
    else if (goingUp && goingLeft)
    {
        colOffset = -100; rowOffset = -100;
    }
    else if (goingDown && goingRight)
    {
        colOffset = 100; rowOffset = 100;
    }
    else if (goingDown && goingLeft)
    {
        colOffset = -100; rowOffset = 100;
    }
    else if (goingUp)
    {
        colOffset = 0; rowOffset = -100;
    }
    else if (goingDown)
    {
        colOffset = 0; rowOffset = 100;
    }
    else if (goingRight)
    {
        colOffset = 100; rowOffset = 0;
    }
    else
    {
        colOffset = -100; rowOffset = 0;
    }

    for (col = previousPosition.first, row = previousPosition.second; col != int(x()) || row != int(y());
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row, color);
        if (blocked_by_piece)
            return true;
    }
    return false;
}
