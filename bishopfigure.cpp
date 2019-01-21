#include "bishopfigure.h"
#include <QBrush>
#include <cmath>

BishopFigure::BishopFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
        setBrush(QPixmap(":/figures images/bishop_white.png").scaledToHeight(100).scaledToWidth(100));
    else
        setBrush(QPixmap(":/figures images/bishop_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool BishopFigure::moveIsValid()
{
    if ((isThereAnythingOnMyWay() || thereIsOtherPieceOnField()) && !isItPossibleToBeat())
        return false;

    int rowOffset = int(std::abs(y() - previousPosition.second));

    if (rowOffset != int(std::abs(x() - previousPosition.first)))
        return false;


    if (isItPossibleToBeat())
    {
        emit beatFigure(rank(), file(), color);
    }

    emit addDangeredFields();
    if (isCheck())
        return false;

    return true;
}

bool BishopFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool BishopFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(rank(), file(), color);
    return occupancy;
}

bool BishopFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - file() > 0;
    bool goingRight = previousPosition.first - rank() < 0;

    if (goingUp && goingRight)
    {
        colOffset = 100;
        rowOffset = -100;
    }
    else if (goingUp && !goingRight)
    {
        colOffset = -100;
        rowOffset = -100;
    }
    else if (!goingUp && goingRight)
    {
        colOffset = 100;
        rowOffset = 100;
    }
    else
    {
        colOffset = -100;
        rowOffset = 100;
    }

    for (col = previousPosition.first, row = previousPosition.second; col != rank() && row != file();
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row, color);
        if (blocked_by_piece)
            return true;
    }
    return false;
}

vecOfPairs BishopFigure::dangeredPositions()
{
    vecOfPairs dangeredPos;
    vecOfPairs possibleDirections;

    possibleDirections = { std::make_pair(100, -100), std::make_pair(-100, -100), std::make_pair(100, 100), std::make_pair(-100, 100) };

    int col = rank();
    int row = file();

    for (auto pD : possibleDirections)
    {
        while(true)
        {
            col += pD.first;
            row += pD.second;
            emit checkIfThereIsSomethingOnMyWay(col, row);
            if (col < 0 || col > 700 || row < 0 || row > 700)
                break;
            dangeredPos.emplace_back(col, row);
            if (blocked_by_piece)
                break;
        }

        blocked_by_piece = false;
        col = rank();
        row = file();
    }

//    for (auto d : dangeredPos)
//    {
//        qDebug() << "(" << d.first << ", " << d.second << ")";
//    }

    return dangeredPos;
}

vecOfPairs BishopFigure::possibleMoves()
{
    return dangeredPositions();
}
