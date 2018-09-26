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
        return false;

    if (!isItPossibleToBeat())
        return true;

    int colOffset = std::abs(horizontalPos() - previousPosition.first);
    int rowOffset = verticalPos() - previousPosition.second;

    if (colOffset == 100 && rowOffset == -100 && color == figureColors::white)
    {
        emit beatFigure(horizontalPos(), verticalPos(), color);
        return true;
    }
    else if (colOffset == 100 && rowOffset == 100 && color == figureColors::black)
    {
        emit beatFigure(horizontalPos(), verticalPos(), color);
        return true;
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
