#include "rookfigure.h"
#include <QBrush>

RookFigure::RookFigure(figureColors type)
{
    setColor(type);
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

}

bool RookFigure::isItPossibleToBeat()
{

}
