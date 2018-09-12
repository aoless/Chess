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
            setPosition(previousPosition.first, previousPosition.second);

        if (previousPosition.first != horizontalPos() || previousPosition.second != verticalPos())
        {
            if (color == figureColors::white)
                emit disableFiguresPickUp(false, figureColors::white);
            else
                emit disableFiguresPickUp(false, figureColors::black);
        }

        changeStateOfPreviousPosition(horizontalPos(), verticalPos());

    }
    else if (mode == unclicked && possible_to_click)
    {
        emit propagateInfoOfAbilityToMove(this);
        // you must disable picking other figures
        mode = clicked;
    }
}

void AbstractFigure::changeStateOfPreviousPosition(int col, int row)
{
    previousPosition.first = col;
    previousPosition.second = row;
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
    blocked_by_piece = blocked;
}

void AbstractFigure::setPosition(int col, int row)
{
    setPos(col, row);
}
