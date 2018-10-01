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
        emit beatFigure(ranks(), files(), color);

    int rowOffset = files() - previousPosition.second;
    int colOffset = ranks() - previousPosition.first;

    if (neverMoved)
    {
        switch (colOffset)
        {
        case 200:
            if (isThereAnythingOnMyWay())
                break;
            emit castling(ranks() + 100, files(), "left");
            neverMoved = false;
            return true;
        case -300:
            if (isThereAnythingOnMyWay())
                break;
            emit castling(ranks() - 100, files(), "right");
            neverMoved = false;
            return true;
        default:
            break;
        }

    }

    bool goingToFarVerticaly = std::abs(colOffset) > 100;
    bool goingToFarHorizontaly = std::abs(rowOffset) > 100;

    if (goingToFarVerticaly || goingToFarHorizontaly)
        return false;

    if (previousPosition.first != ranks() || previousPosition.second != files())
        neverMoved = false;
    return true;
}

bool KingFigure::isItPossibleToBeat()
{
    return false;
}

bool KingFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(ranks(), files(), color);
    return occupancy;
}

bool KingFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;

    bool goingRight = previousPosition.first - ranks() < 0;
    bool goingLeft = previousPosition.first - ranks() > 0;

    if (goingRight)
    {
        colOffset = 100; rowOffset = 0;
    }
    else if (goingLeft)
    {
        colOffset = -100; rowOffset = 0;
    }

    for (col = previousPosition.first, row = previousPosition.second; col != ranks() || row != files();
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row, color);
        if (blocked_by_piece)
            return true;
    }

    return false;
}
