#include "pawnfigure.h"
#include <QBrush>

PawnFigure::PawnFigure()
{
    this->setRect(0, 0, 100, 100);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setBrush(QPixmap(":/figures images/pionek.PNG").scaledToHeight(100).scaledToWidth(100));
}
