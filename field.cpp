#include "field.h"
#include <QDebug>
#include <QGraphicsView>

Field::Field(int row_, int col_)
{
    position = std::make_pair(row_, col_);
    setRect(0, 0, 100, 100);
    if (position.first % 2 == 0 && position.second % 2 != 0)
    {
        setVariant(black);
    }
    else if (position.first % 2 != 0 && position.second % 2 == 0)
    {
        setVariant(black);
    }
    else
    {
        setVariant(white);
    }

    setAcceptHoverEvents(true);
}

void Field::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    QString c  = QString::number(this->x()) + " " + QString::number(this->y());
    emit showCoordinates(c);
    emit sendCoordinates(this->x(), this->y());
    update();
}


void Field::setVariant(Field::VARIANT color)
{
    if (color == white)
    {
        fieldColor = QPixmap(":/white.jpg");
        this->setBrush(QBrush(fieldColor));
    }
    else
    {
        fieldColor = QPixmap(":/dark.jpg");
        this->setBrush(QBrush(fieldColor));
    }
}
