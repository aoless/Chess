#include "rookfigure.h"
#include <QBrush>

RookFigure::RookFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
        setBrush(QPixmap(":/figures images/rook_white.png").scaledToHeight(100).scaledToWidth(100));
    else
        setBrush(QPixmap(":/figures images/rook_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool RookFigure::moveIsValid()
{
    int rowOffset = int(std::abs(files() - previousPosition.second));
    int colOffset = int(std::abs(ranks() - previousPosition.first));

    if (!((rowOffset > 0 && colOffset == 0) || (rowOffset == 0 && colOffset > 0)))
        return false;

    if ((isThereAnythingOnMyWay() || thereIsOtherPieceOnField()) && !isItPossibleToBeat())
        return false;

    if (isItPossibleToBeat())
        emit beatFigure(ranks(), files(), color);

    emit castlingBlocker(color);
    return true;
}

bool RookFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool RookFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(ranks(), files(), color);
    return occupancy;
}

bool RookFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - files() > 0;
    bool goingRight = previousPosition.first - ranks() < 0;
    bool goingLeft = previousPosition.first - ranks() > 0;
    bool goingDown = previousPosition.second - files() < 0;

    if (goingUp)
    {
        colOffset = 0; rowOffset = -100;
    }
    else if (goingRight)
    {
        colOffset = 100; rowOffset = 0;
    }
    else if (goingLeft)
    {
        colOffset = -100; rowOffset = 0;
    }
    else if(goingDown)
    {
        colOffset = 0; rowOffset = 100;
    }

    for (col = previousPosition.first, row = previousPosition.second; col != ranks() && row != files();
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row, color);
        if (blocked_by_piece)
        {
            return true;
        }
    }
    return false;
}
