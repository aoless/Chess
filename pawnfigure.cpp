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

    int colOffset = std::abs(rank() - previousPosition.first);
    int rowOffset = file() - previousPosition.second;

    if (isItPossibleToBeat())
    {
        if (colOffset == 100 && rowOffset == -100 && color == figureColors::white)
        {
            emit beatFigure(rank(), file(), color);
            dangeredPositions();
            return true;
        }
        else if (colOffset == 100 && rowOffset == 100 && color == figureColors::black)
        {
            emit beatFigure(rank(), file(), color);
            dangeredPositions();
            return true;
        }
        else
        {
            return false;
        }
    }

    if (rank() == previousPosition.first && (file() == previousPosition.second - offset ||
       (file() == previousPosition.second - offset - begginingOffset)))
    {
        beggining = false;
        dangeredPositions();
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
    emit checkIfOtherFigureHasSamePosition(rank(), file(), color);
    return occupancy;
}

vecOfPairs PawnFigure::dangeredPositions()
{
    vecOfPairs dangeredPos;
    dangeredPos.emplace_back(rank() + 100, file() - 100);
    dangeredPos.emplace_back(rank() - 100, file() - 100);

    for (auto d : dangeredPos)
    {
        qDebug() << d.first << " " << d.second;
    }

    return dangeredPos;
}
