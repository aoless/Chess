#include "abstractfigure.h"
#include <QDebug>

AbstractFigure::AbstractFigure(QObject *parent) : QObject(parent)
{
}

void AbstractFigure::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    if (mode == clicked)
    {
        emit propagateInfoOfDisabilityToMove(this);
        mode = unclicked;
        if (!moveIsValid())
        {
            setPosition(previousPosition.first, previousPosition.second);
        }
        emit unableToPickOtherFigures(true);
        changeStateOfPreviousPosition(this->x(), this->y());
    }
    else if (mode == unclicked && possible_to_click)
    {
        emit unableToPickOtherFigures(false);
        emit propagateInfoOfAbilityToMove(this);
        mode = clicked;
    }
}

void AbstractFigure::changeStateOfPreviousPosition(int x, int y)
{
    previousPosition.first = x;
    previousPosition.second = y;
}

bool AbstractFigure::isWhite()
{
    return color == figureColors::white ? true : false;
}

void AbstractFigure::setColor(figureColors c)
{
    color = c;
}

void AbstractFigure::changePossibilityToClick(bool possibility)
{
    possible_to_click = possibility;
}

void AbstractFigure::fieldIsOccupied(bool occupied)
{
    occupancy = occupied;
}

void AbstractFigure::thereIsSomethingOnTheWay(bool blocked)
{
    blockedByPiece = blocked;
}

void AbstractFigure::setPosition(int col, int row)
{
    setPos(col, row);
}
