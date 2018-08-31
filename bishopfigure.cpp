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
    // position does not change
    if (this->x() == previousPosition.first &&
            this->y() == previousPosition.second)
        return true;

    int rowOffset = abs(this->y() - previousPosition.second);

    if ((rowOffset == abs(this->x() - previousPosition.first)))
    {
        if (thereIsNoOtherPieceOnField() && isThereAnythingOnMyWay())
            return true;
        else
            return false;
    }

    return false;
}

bool BishopFigure::isItPossibleToBeat()
{

}

bool BishopFigure::thereIsNoOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(this->x(), this->y());
}

bool BishopFigure::isThereAnythingOnMyWay()
{
    qreal col, row;
    for (col = previousPosition.first, row = previousPosition.second; col != this->x() && row != this->y();
            col -= 100, row += 100)
    {
        emit checkIfOtherFigureHasSamePosition(this->x(), this->y());
        return occupancy;
    }
}
