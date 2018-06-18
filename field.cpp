#include "field.h"
#include <QDebug>

Field::Field(int row_, int col_)
{
    position = std::make_pair(row_, col_);
    rect = new QGraphicsRectItem(0, 0, size, size);
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

    rect->setAcceptHoverEvents(true);
}

void Field::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    QString c("dupa!");
    emit showCoordinates(c);
    update();
}

void Field::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    qDebug() << "dupcia blada";
}

void Field::setVariant(Field::VARIANT color)
{
    if (color == white)
    {
        fieldColor = QPixmap(":/white.jpg");
        rect->setBrush(QBrush(fieldColor));
    }
    else
    {
        fieldColor = QPixmap(":/dark.jpg");
        rect->setBrush(QBrush(fieldColor));
    }
}
