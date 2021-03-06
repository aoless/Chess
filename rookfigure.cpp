#include "rookfigure.h"
#include <QBrush>

RookFigure::RookFigure(figureColors type)
{
    color = type;
    setRect(0, 0, 100, 100);

    if (isWhite())
        setBrush(QPixmap(":/figures images/rook_white.png").scaledToHeight(100).scaledToWidth(100));
    else
        setBrush(QPixmap(":/figures images/rook_black.png").scaledToHeight(100).scaledToWidth(100));
}

bool RookFigure::moveIsValid()
{
    int rowOffset = int(std::abs(file() - previousPosition.second));
    int colOffset = int(std::abs(rank() - previousPosition.first));

    if (!((rowOffset > 0 && colOffset == 0) || (rowOffset == 0 && colOffset > 0)))
        return false;

    if ((isThereAnythingOnMyWay() || thereIsOtherPieceOnField()) && !isItPossibleToBeat())
        return false;

    emit addDangeredFields();
    if (isCheck())
        return false;

    if (isItPossibleToBeat())
        emit beatFigure(rank(), file(), color);

    emit castlingBlocker(color);

    return true;
}


bool RookFigure::moveIsValidWrapper(int col, int row)
{
    int rowOffset = int(std::abs(row - previousPosition.second));
    int colOffset = int(std::abs(col - previousPosition.first));

    if (!((rowOffset > 0 && colOffset == 0) || (rowOffset == 0 && colOffset > 0)))
        return false;

    if ((isThereAnythingOnMyWay() || thereIsOtherPieceOnField()) && !isItPossibleToBeat())
        return false;

    if (isCheck())
        return false;

    return true;
}



bool RookFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool RookFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(rank(), file(), color);
    return occupancy;
}

bool RookFigure::isThereAnythingOnMyWay()
{
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - file() > 0;
    bool goingRight = previousPosition.first - rank() < 0;
    bool goingLeft = previousPosition.first - rank() > 0;
    bool goingDown = previousPosition.second - file() < 0;

    if (goingUp)
    {
        colOffset = 0; rowOffset = -100;
    }
    else if (goingRight)
    {
        colOffset = 100; rowOffset = 0;
    }
    else if (goingLeft)
    {
        colOffset = -100; rowOffset = 0;
    }
    else if(goingDown)
    {
        colOffset = 0; rowOffset = 100;
    }

    for (col = previousPosition.first, row = previousPosition.second; col != rank() || row != file();
         col += colOffset, row += rowOffset)
    {
        emit checkIfThereIsSomethingOnMyWay(col, row, color);
        if (blocked_by_piece)
        {
            return true;
        }
    }
    return false;
}

vecOfPairs RookFigure::dangeredPositions()
{
    vecOfPairs dangeredPos;
    vecOfPairs possibleDirections;

    possibleDirections = { std::make_pair(100, 0), std::make_pair(-100, 0), std::make_pair(0, 100), std::make_pair(0, -100) };
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

//    for (auto d : dangeredPos)
//    {
//        qDebug() << "(" << d.first << ", " << d.second << ")";
//    }

    return dangeredPos;
}

vecOfPairs RookFigure::possibleMoves()
{
    return dangeredPositions();
}
