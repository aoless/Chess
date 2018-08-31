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
        // check if there is no piece on the way!
        // if not:
        return true;
        // else:
        // return false
    }


    return false;


}

bool BishopFigure::isItPossibleToBeat()
{

}

bool BishopFigure::thereIsNoOtherPieceOnField()
{

}
