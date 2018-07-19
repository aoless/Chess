#include "knightfigure.h"
#include <QBrush>

KnightFigure::KnightFigure(figureColors type)
{
    setColor(type);
    this->setRect(0, 0, 100, 100);

    if (isWhite())
    {
        this->setBrush(QPixmap(":/figures images/knight_white.png").scaledToHeight(100).scaledToWidth(100));
    }
    else
    {
        this->setBrush(QPixmap(":/figures images/knight_black.png").scaledToHeight(100).scaledToWidth(100));
    }
}

bool KnightFigure::moveIsValid()
{

}

bool KnightFigure::isItPossibleToBeat()
{

}
