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
    if (thereIsOtherPieceOnField() && !possible_to_beat)
        return false;

    if (possible_to_beat)
        beatFigure(horizontalPos(), verticalPos(), color);

    int colJump = std::abs(previousPosition.second - verticalPos());
    int rowJump = std::abs(previousPosition.first - horizontalPos());

    if (colJump == 100 && rowJump == 200)
        return true;
    else if (colJump == 200 && rowJump == 100)
        return true;
    else
        return false;
}

bool KnightFigure::isItPossibleToBeat()
{
    return false;
}

bool KnightFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(horizontalPos(), verticalPos(), color);
    return occupancy;
}
