#include "pawnfigure.h"
#include <QBrush>

PawnFigure::PawnFigure(color type)
{
    this->setRect(0, 0, 100, 100);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    if (type == white)
    {
        this->setBrush(QPixmap(":/figures images/pawn_white.png").scaledToHeight(100).scaledToWidth(100));
    }
    else
    {
        this->setBrush(QPixmap(":/figures images/pawn_black2.png").scaledToHeight(100).scaledToWidth(100));
    }
}
