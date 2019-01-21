#include "kingfigure.h"
#include <QBrush>

KingFigure::KingFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
        setBrush(QPixmap(":/figures images/king_white.png").scaledToHeight(100).scaledToWidth(100));
    else
        setBrush(QPixmap(":/figures images/king_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool KingFigure::moveIsValid()
{
    if (thereIsOtherPieceOnField() && !isItPossibleToBeat())
        return false;

    emit addDangeredFields();
    if (isCheck())
        return false;

    if(isItPossibleToBeat())
        emit beatFigure(rank(), file(), color);

    int rowOffset = file() - previousPosition.second;
    int colOffset = rank() - previousPosition.first;

    if (never_moved)
    {
        switch (colOffset)
        {
        case 200:
            if (isThereAnythingOnMyWay())
                break;
            emit castling(rank() + 100, file(), "left");
            never_moved = false;
            return true;
        case -300:
            if (isThereAnythingOnMyWay())
                break;
            emit castling(rank() - 100, file(), "right");
            never_moved = false;
            return true;
        default:
            break;
        }

    }

    bool goingToFarVerticaly = std::abs(colOffset) > 100;
    bool goingToFarHorizontaly = std::abs(rowOffset) > 100;

    if (goingToFarVerticaly || goingToFarHorizontaly)
        return false;

    if (previousPosition.first != rank() || previousPosition.second != file())
        never_moved = false;

    // dangeredPositions();
    return true;
}

bool KingFigure::moveIsValidWrapper(int col, int row)
{
    emit checkIfOtherFigureHasSamePosition(col, row, color);
    if (blocked_by_piece && !isItPossibleToBeat())
    {
        blocked_by_piece = false;
        return false;
    }

    if (isItPossibleToBeat())
        return true;

    return true;

}

bool KingFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool KingFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(rank(), file(), color);
    return occupancy;
}

bool KingFigure::isThereAnythingOnMyWay()
{
    emit addDangeredFields();
    if (isCheck())
        return false;

    int col, row;
    int colOffset = 0;
    int rowOffset = 0;

    bool goingRight = previousPosition.first - rank() < 0;
    bool goingLeft = previousPosition.first - rank() > 0;

    if (goingRight)
    {
        colOffset = 100; rowOffset = 0;
    }
    else if (goingLeft)
    {
        colOffset = -100; rowOffset = 0;
    }

    for (col = previousPosition.first, row = previousPosition.second; col != rank() || row != file();
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row, color);
        if (blocked_by_piece)
            return true;
    }

    return false;
}

vecOfPairs KingFigure::dangeredPositions()
{
    vecOfPairs dangeredPos;
    vecOfPairs possibleDirections;

    possibleDirections = { std::make_pair(100, 0), std::make_pair(-100, 0), std::make_pair(0, 100), std::make_pair(0, -100),
                           std::make_pair(100, -100), std::make_pair(-100, -100), std::make_pair(100, 100), std::make_pair(-100, 100)};
    int col = rank();
    int row = file();

    for (auto pD : possibleDirections)
    {
        col += pD.first; row += pD.second;
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

vecOfPairs KingFigure::possibleMoves()
{
    vecOfPairs possibleMovesVec;
    int step = 100;
    if (!isWhite())
        step = -step;

    possibleMovesVec.emplace_back(rank() + step, file());

    return possibleMovesVec;
}
