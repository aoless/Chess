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
        if (previousPosition.first != int(this->x()) || previousPosition.second != int(this->y()))
        {
            if (color == figureColors::white)
                emit disableFiguresPickUp(false, figureColors::white);
            else
                emit disableFiguresPickUp(false, figureColors::black);
        }

        changeStateOfPreviousPosition(int(this->x()), int(this->y()));

    }
    else if (mode == unclicked && possible_to_click)
    {
        emit propagateInfoOfAbilityToMove(this);
        mode = clicked;
    }
}

void AbstractFigure::changeStateOfPreviousPosition(int x, int y)
{
    previousPosition.first = x;
    previousPosition.second = y;
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
