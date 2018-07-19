#include "abstractfigure.h"
#include <QDebug>

AbstractFigure::AbstractFigure(QObject *parent) : QObject(parent)
{
}

void AbstractFigure::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    if (mode == clicked)
    {
        emit disconnectThisShit(this);
        mode = unclicked;
        if (!moveIsValid())
        {
            setPosition(previousPosition.first, previousPosition.second);
        }

        changeStateOfPreviousPosition(row, col);
        emit unableToPickOtherFigures(true);
    }
    else if (mode == unclicked && possible_to_click)
    {
        emit unableToPickOtherFigures(false);
        emit connectThisShit(this);
        mode = clicked;
    }

}

void AbstractFigure::changeStateOfPreviousPosition(qreal x, qreal y)
{
    previousPosition.first = x;
    previousPosition.second = y;
}

bool AbstractFigure::isWhite()
{
    if (color == white)
        return true;
    return false;
}

void AbstractFigure::setColor(figureColors c)
{
    color = c;
}

void AbstractFigure::changePossibilityToClick(bool possibility)
{
    possible_to_click = possibility;
}

void AbstractFigure::setPosition(qreal col, qreal row)
{
    setPos(col, row);
}
