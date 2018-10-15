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
    int colJump = std::abs(previousPosition.second - file());
    int rowJump = std::abs(previousPosition.first - rank());

    if ((colJump == 100 && rowJump == 200) || (colJump == 200 && rowJump == 100))
    {
        if (thereIsOtherPieceOnField() && !isItPossibleToBeat())
            return false;

        if (isItPossibleToBeat())
            beatFigure(rank(), file(), color);

    }
    else
        return false;

    // dangeredPositions();
    return true;
}

bool KnightFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool KnightFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(rank(), file(), color);
    return occupancy;
}

vecOfPairs KnightFigure::dangeredPositions()
{
    vecOfPairs dangeredPos;
    vecOfPairs possibleDirections;


    possibleDirections = { std::make_pair(200, 100), std::make_pair(100, 200), std::make_pair(-200, 100), std::make_pair(-100, 200),
                           std::make_pair(200, -100), std::make_pair(100, -200), std::make_pair(-200, -100), std::make_pair(-100, -200)};

    int col = rank();
    int row = file();

    for (auto pD : possibleDirections)
    {
        col += pD.first;
        row += pD.second;
        if ((col > 700 || col < 0) || (row > 700 || row < 0))
        {
            col = rank();
            row = file();
            continue;
        }
        dangeredPos.emplace_back(col, row);

        col = rank();
        row = file();
    }

//    for (auto d : dangeredPos)
//    {
//        qDebug() << "(" << d.first << ", " << d.second << ")";
//    }

    return dangeredPos;
}
