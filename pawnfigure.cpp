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

    if (thereIsOtherPieceOnField())
        return false;

    if (isItPossibleToBeat())
        if (int(x()) == previousPosition.first + offset ||
                (int(x()) == previousPosition.first - offset &&
                 int(y()) == previousPosition.second - offset))
        {
            beggining = false;
            return true;
        }
        else
        {
            qDebug() << "There is nothing to beat";
            return false;
        }
    else if (int(x()) == previousPosition.first &&
              (int(y()) == previousPosition.second - offset ||
              (int(y()) == previousPosition.second - offset - begginingOffset)))
        {
            beggining = false;
            return true;
        }

    return false;
}

bool PawnFigure::isItPossibleToBeat()
{
    return false;
}

bool PawnFigure::isItBegginingOfGame()
{
    return beggining;
}

bool PawnFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(int(x()), int(y()), color);
    return occupancy;
}
