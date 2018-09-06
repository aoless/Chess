#include "queenfigure.h"
#include <QBrush>

QueenFigure::QueenFigure(figureColors type)
{
    setColor(type);
    this->setRect(0, 0, 100, 100);

    if (isWhite())
    {
        this->setBrush(QPixmap(":/figures images/queen_white.png").scaledToHeight(100).scaledToWidth(100));
    }
    else
    {
        this->setBrush(QPixmap(":/figures images/queen_black.png").scaledToHeight(100).scaledToWidth(100));
    }
}

bool QueenFigure::moveIsValid()
{
    // position does not change
    if (int(this->x()) == previousPosition.first && int(this->y()) == previousPosition.second)
        return true;

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
    emit checkIfOtherFigureHasSamePosition(int(this->x()), int(this->y()));
    return occupancy;
}

bool QueenFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - int(this->y()) > 0;
    bool goingDown = previousPosition.second - int(this->y()) < 0;
    bool goingRight = previousPosition.first - int(this->x()) < 0;
    bool goingLeft = previousPosition.first - int(this->x()) > 0;

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
