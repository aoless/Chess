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
        emit beatFigure(ranks(), files(), color);

    return true;
}

bool BishopFigure::isItPossibleToBeat()
{
    return possible_to_beat;
}

bool BishopFigure::thereIsOtherPieceOnField()
{
    emit checkIfOtherFigureHasSamePosition(ranks(), files(), color);
    return occupancy;
}

bool BishopFigure::isThereAnythingOnMyWay()
{
    qDebug() << "Ja tu wchodze";
    int col, row;
    int colOffset = 0;
    int rowOffset = 0;
    bool goingUp = previousPosition.second - files() > 0;
    bool goingRight = previousPosition.first - ranks() < 0;

    qDebug() << previousPosition.second - files();
    qDebug() << previousPosition.first - ranks();

    if (goingUp && goingRight)
    {
        qDebug() << "prawy rog";
        colOffset = 100;
        rowOffset = -100;
    }
    else if (goingUp && !goingRight)
    {
        qDebug() << "lewy rog";
        colOffset = -100;
        rowOffset = -100;
    }
    else if (!goingUp && goingRight)
    {
        qDebug() << "dolny prawy rog";
        colOffset = 100;
        rowOffset = 100;
    }
    else
    {
        qDebug() << "dolny lewy rog";
        colOffset = -100;
        rowOffset = 100;
    }

    for (col = previousPosition.first, row = previousPosition.second; col != ranks() && row != files();
         col += colOffset, row += rowOffset)
    {
        qDebug() << col << " " << row;
        emit checkIfThereIsSomethingOnMyWay(col, row, color);
        if (blocked_by_piece)
            return true;
    }
    return false;
}
