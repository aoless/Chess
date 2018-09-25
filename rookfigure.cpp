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
    if ((isThereAnythingOnMyWay() || thereIsOtherPieceOnField()) && !isItPossibleToBeat())
        return false;

    qDebug() << "A tu cos robie??";
    if (isItPossibleToBeat())
        emit beatFigure(horizontalPos(), verticalPos(), color);

    int rowOffset = int(std::abs(verticalPos() - previousPosition.second));
    int colOffset = int(std::abs(horizontalPos() - previousPosition.first));

    if ((rowOffset > 0 && colOffset == 0) || (rowOffset == 0 && colOffset > 0))
        return true;

    return false;
}

bool RookFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool RookFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(horizontalPos(), verticalPos(), color);
    return occupancy;
}

bool RookFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - verticalPos() > 0;
    bool goingRight = previousPosition.first - horizontalPos() < 0;

    if (goingUp)
    {
        colOffset = 0;
        rowOffset = -100;
    }
    else if (!goingUp && !goingRight)
    {
        colOffset = 0;
        rowOffset = 100;
    }
    else if (goingRight)
    {
        colOffset = 100;
        rowOffset = 0;
    }
    else
    {
        colOffset = -100;
        rowOffset = 0;
    }

    for (col = previousPosition.first, row = previousPosition.second; col != horizontalPos() || row != verticalPos();
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
