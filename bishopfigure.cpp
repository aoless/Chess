#include "bishopfigure.h"
#include <QBrush>
#include <cmath>

BishopFigure::BishopFigure(figureColors type)
{
    setColor(type);
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
    qDebug() << "Check if move is valid";
    // position does not change
    if (int(this->x()) == previousPosition.first &&
            int(this->y()) == previousPosition.second)
        return true;

    if (isThereAnythingOnMyWay())
    {
        qDebug() << "There is something on my way";
        return false;
    }

    if (!thereIsOtherPieceOnField())
    {
        qDebug() << "Free";
    }
    else
    {
        qDebug() << "Occupied";
        return false;
    }


    int rowOffset = int(std::abs(this->y() - previousPosition.second));

    if (rowOffset == int(std::abs(this->x() - previousPosition.first)))
    {
        return true;
    }

    return false;
}

bool BishopFigure::isItPossibleToBeat()
{
    return false;
}

bool BishopFigure::thereIsOtherPieceOnField()
{
    qDebug() << "anythin on my way";
    emit checkIfOtherFigureHasSamePosition(int(this->x()), int(this->y()));
    return occupancy;
}

bool BishopFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int offset = 0;
    if (previousPosition.first - int(this->x()) < 0)
    {
        offset = 100;
    }
    else if (previousPosition.first - int(this->x() > 0))
    {
        offset = -100;
    }
    for (col = previousPosition.first, row = previousPosition.second; col != int(this->x()) && row != int(this->y());
         col += offset, row -= 100)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row);
        if (blockedByPiece)
            return true;
    }

    return false;
}
