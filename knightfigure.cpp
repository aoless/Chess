#include "knightfigure.h"
#include <QBrush>

KnightFigure::KnightFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
    {
        setBrush(QPixmap(":/figures images/knight_white.png").scaledToHeight(100).scaledToWidth(100));
        changePossibilityToClick(true);
    }
    else
        setBrush(QPixmap(":/figures images/knight_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool KnightFigure::moveIsValid()
{
    int colJump = std::abs(previousPosition.second - files());
    int rowJump = std::abs(previousPosition.first - ranks());

    if ((colJump == 100 && rowJump == 200) || (colJump == 200 && rowJump == 100))
    {
        if (thereIsOtherPieceOnField() && !isItPossibleToBeat())
            return false;

        if (isItPossibleToBeat())
            beatFigure(ranks(), files(), color);

    }
    else
        return false;

    return true;
}

bool KnightFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool KnightFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(ranks(), files(), color);
    return occupancy;
}
