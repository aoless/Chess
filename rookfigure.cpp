#include "rookfigure.h"
#include <QBrush>

RookFigure::RookFigure(figureColors type)
{
    color = type;
    this->setRect(0, 0, 100, 100);

    if (isWhite())
    {
        this->setBrush(QPixmap(":/figures images/rook_white.png").scaledToHeight(100).scaledToWidth(100));
    }
    else
    {
        this->setBrush(QPixmap(":/figures images/rook_black.png").scaledToHeight(100).scaledToWidth(100));
    }
}

bool RookFigure::moveIsValid()
{
    if (isThereAnythingOnMyWay() || thereIsOtherPieceOnField())
        return false;

    int rowOffset = int(std::abs(this->y() - previousPosition.second));
    int colOffset = int(std::abs(this->x() - previousPosition.first));

    if ((rowOffset > 0 && colOffset == 0) || (rowOffset == 0 && colOffset > 0))
        return true;

    return false;
}

bool RookFigure::isItPossibleToBeat()
{
    return false;
}

bool RookFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(int(this->x()), int(this->y()));
    if (occupancy)
    {
        qDebug() << "This field is occupied";
    }
    return occupancy;
}

bool RookFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - int(this->y()) > 0;
    bool goingRight = previousPosition.first - int(this->x()) < 0;

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

    for (col = previousPosition.first, row = previousPosition.second; col != int(this->x()) || row != int(this->y());
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row);
        if (blockedByPiece)
        {
            qDebug() << "There is something on my way!";
            return true;
        }
    }
    return false;
}
