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

}

bool QueenFigure::isItPossibleToBeat()
{

}
