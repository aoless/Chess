#include "pawnfigure.h"
#include <QBrush>

PawnFigure::PawnFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
    {
        setBrush(QPixmap(":/figures images/pawn_white.png").scaledToHeight(100).scaledToWidth(100));
        changePossibilityToClick(true);
    }
    else
        setBrush(QPixmap(":/figures images/pawn_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool PawnFigure::moveIsValid()
{
    int offset;
    int begginingOffset = 0;

    isWhite() ? offset = 100 : offset = -100;
    isItBegginingOfGame() ? begginingOffset = offset : begginingOffset = 0;

    if (thereIsOtherPieceOnField() && !isItPossibleToBeat())
    {
        return false;
    }

    if (isItPossibleToBeat())
    {
        if (std::abs(horizontalPos() - previousPosition.first) == 100 &&
            std::abs(verticalPos() - previousPosition.second) == 100)
        {
            emit beatFigure(horizontalPos(), verticalPos(), color);
            return true;
        }
        else
        {
            return false;
        }
    }

    if (horizontalPos() == previousPosition.first && (verticalPos() == previousPosition.second - offset ||
       (verticalPos() == previousPosition.second - offset - begginingOffset)))
    {
        beggining = false;
        return true;
    }

    return false;
}

bool PawnFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool PawnFigure::isItBegginingOfGame()
{
    return beggining;
}

bool PawnFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(horizontalPos(), verticalPos(), color);
    return occupancy;
}
