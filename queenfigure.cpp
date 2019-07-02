#include "queenfigure.h"
#include <QBrush>

QueenFigure::QueenFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
        setBrush(QPixmap(":/figures images/queen_white.png").scaledToHeight(100).scaledToWidth(100));
    else
        setBrush(QPixmap(":/figures images/queen_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool QueenFigure::moveIsValid()
{
    int rowOffset = int(std::abs(file() - previousPosition.second));
    int colOffset = int(std::abs(rank() - previousPosition.first));

    if (!((rowOffset > 0 && colOffset == 0) || (rowOffset == 0 && colOffset > 0) || (rowOffset == colOffset)))
        return false;
    if ((isThereAnythingOnMyWay() || thereIsOtherPieceOnField()) && !isItPossibleToBeat())
    {
        return false;
    }

    if (isItPossibleToBeat())
    {
        emit beatFigure(rank(), file(), color);
    }

//    if (isCheck())      // problem z kolejnością, nie ma możliwości zbicia grożącego pionka
//    {
//        return false;
//    }

    // dangeredPositions();
    emit addDangeredFields();
    return true;
}


bool QueenFigure::moveIsValidWrapper(int col, int row)
{
    setPos(col, row);
    int rowOffset = int(std::abs(file() - previousPosition.second));
    int colOffset = int(std::abs(rank() - previousPosition.first));

    if (!((rowOffset > 0 && colOffset == 0) || (rowOffset == 0 && colOffset > 0) || (rowOffset == colOffset)))
        return false;

    if (isThereAnythingOnMyWay() || thereIsOtherPieceOnField())
    {
        setPos(previousPosition.first, previousPosition.second);
        return false;
    }

    if (isCheck())  // problem z kolejnością, nie ma możliwości zbicia grożącego pionka
    {
        setPos(previousPosition.first, previousPosition.second);
        return false;
    }

    if (isItPossibleToBeat())
    {
        setPos(previousPosition.first, previousPosition.second);
        return true;
    }

    setPos(previousPosition.first, previousPosition.second);
    return true;
}

bool QueenFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool QueenFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(rank(), file(), color);
    qDebug() << occupancy;
    return occupancy;
}

bool QueenFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - file() > 0;
    bool goingDown = previousPosition.second - file() < 0;
    bool goingRight = previousPosition.first - rank() < 0;
    bool goingLeft = previousPosition.first - rank() > 0;

    if (goingUp && goingRight)
    {
        colOffset = 100; rowOffset = -100;
    }
    else if (goingUp && goingLeft)
    {
        colOffset = -100; rowOffset = -100;
    }
    else if (goingDown && goingRight)
    {
        colOffset = 100; rowOffset = 100;
    }
    else if (goingDown && goingLeft)
    {
        colOffset = -100; rowOffset = 100;
    }
    else if (goingUp)
    {
        colOffset = 0; rowOffset = -100;
    }
    else if (goingDown)
    {
        colOffset = 0; rowOffset = 100;
    }
    else if (goingRight)
    {
        colOffset = 100; rowOffset = 0;
    }
    else
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

vecOfPairs QueenFigure::dangeredPositions()
{
    vecOfPairs dangeredPos;
    vecOfPairs possibleDirections;

    possibleDirections = { std::make_pair(100, 0), std::make_pair(-100, 0), std::make_pair(0, 100), std::make_pair(0, -100),
                           std::make_pair(100, -100), std::make_pair(-100, -100), std::make_pair(100, 100), std::make_pair(-100, 100)};
    int col = rank();
    int row = file();

    for (auto pD : possibleDirections)
    {
        while(true)
        {
            col += pD.first; row += pD.second;
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

    return dangeredPos;
}

vecOfPairs QueenFigure::possibleMoves()
{
    return dangeredPositions();
}
