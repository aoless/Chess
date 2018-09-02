#include "kingfigure.h"
#include <QBrush>

KingFigure::KingFigure(figureColors type)
{
    setColor(type);
    this->setRect(0, 0, 100, 100);

    if (isWhite())
    {
        this->setBrush(QPixmap(":/figures images/king_white.png").scaledToHeight(100).scaledToWidth(100));
    }
    else
    {
        this->setBrush(QPixmap(":/figures images/king_black.png").scaledToHeight(100).scaledToWidth(100));
    }
}

bool KingFigure::moveIsValid()
{
    return true;
}

bool KingFigure::isItPossibleToBeat()
{
    return false;
}

bool KingFigure::thereIsNoOtherPieceOnField()
{
    return true;
}
