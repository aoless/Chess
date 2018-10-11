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
        emit beatFigure(rank(), file(), color);

    dangeredPositions();
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

    std::pair<int, int> rightUpperCorner(100, -100);
    std::pair<int, int> leftUpperCorner(-100, -100);
    std::pair<int, int> rightDownCorner(100, 100);
    std::pair<int, int> leftDownCorner(-100, 100);

    possibleDirections.push_back(rightUpperCorner);
    possibleDirections.push_back(leftUpperCorner);
    possibleDirections.push_back(rightDownCorner);
    possibleDirections.push_back(leftDownCorner);

    int col = rank();
    int row = file();

    for (auto pD : possibleDirections)
    {
        qDebug() << "==========";
        while(((col < 700 && col > 0) && (row < 700 && row > 0)))
        {
            col += pD.first;
            row += pD.second;
            emit checkIfThereIsSomethingOnMyWay(col, row, color);
            qDebug() << col << " " << row;
            if (blocked_by_piece)
                break;
            dangeredPos.emplace_back(rank() + pD.first, file() + pD.second);
        }

        blocked_by_piece = false;
        col = rank();
        row = file();

    }

    for (auto d : dangeredPos)
    {
        qDebug() << d.first << " " << d.second;
    }

    return dangeredPos;
}
