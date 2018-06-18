#include "field.h"

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
