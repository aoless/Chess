#include "pawnfigure.h"
#include <QBrush>

PawnFigure::PawnFigure(figureColors type)
{
    setColor(type);
    this->setRect(0, 0, 100, 100);

    if (isWhite())
    {
        this->setBrush(QPixmap(":/figures images/pawn_white.png").scaledToHeight(100).scaledToWidth(100));
    }
    else
    {
        this->setBrush(QPixmap(":/figures images/pawn_black.png").scaledToHeight(100).scaledToWidth(100));
    }
}

bool PawnFigure::moveIsValid()
{
    //position does not change
    if (this->x() == int(previousPosition.first) && this->y() == int(previousPosition.second))
        return true;

    int offset;
    int begginingOffset = 0;

    isWhite() ? offset = 100 : offset = -100;
    isItBegginingOfGame() ? begginingOffset = offset : begginingOffset = 0;

    if (thereIsOtherPieceOnField())
        return false;

    if (isItPossibleToBeat())
        if (int(this->x()) == previousPosition.first + offset ||
                (int(this->x()) == previousPosition.first - offset &&
                 int(this->y()) == previousPosition.second - offset))
        {
            beggining = false;
            return true;
        }
        else
        {
            qDebug() << "There is nothing to beat";
            return false;
        }
    else if (int(this->x()) == previousPosition.first &&
              (int(this->y()) == previousPosition.second - offset ||
              (int(this->y()) == previousPosition.second - offset - begginingOffset)))
        {
            beggining = false;
            return true;
        }

    return false;
}

bool PawnFigure::isItPossibleToBeat()
{
    // is there a figure on that field?
    // send field checker
    return false;
}

bool PawnFigure::isItBegginingOfGame()
{
    return beggining;
}

bool PawnFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(int(this->x()), int(this->y()));
    return occupancy;
}
