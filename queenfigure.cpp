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
    int rowOffset = int(std::abs(verticalPos() - previousPosition.second));
    int colOffset = int(std::abs(horizontalPos() - previousPosition.first));

    if (rowOffset > 0 && colOffset == 0)
    {
        if ((isThereAnythingOnMyWay() || thereIsOtherPieceOnField()) && !isItPossibleToBeat())
            return false;
    }
    else if (rowOffset == 0 && colOffset > 0)
    {
        if ((isThereAnythingOnMyWay() || thereIsOtherPieceOnField()) && !isItPossibleToBeat())
            return false;
    }
    else if (rowOffset == colOffset)
    {
        if ((isThereAnythingOnMyWay() || thereIsOtherPieceOnField()) && !isItPossibleToBeat())
            return false;
    }
    else
    {
        return false;
    }

    if (possible_to_beat)
        emit beatFigure(horizontalPos(), verticalPos(), color);

    return true;
}

bool QueenFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool QueenFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(horizontalPos(), verticalPos(), color);
    return occupancy;
}

bool QueenFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - verticalPos() > 0;
    bool goingDown = previousPosition.second - verticalPos() < 0;
    bool goingRight = previousPosition.first - horizontalPos() < 0;
    bool goingLeft = previousPosition.first - horizontalPos() > 0;

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

    for (col = previousPosition.first, row = previousPosition.second; col != horizontalPos() || row != verticalPos();
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row, color);
        if (blocked_by_piece)
            return true;
    }

    qDebug() << "nie ma nic na mojej drodze";
    return false;
}
