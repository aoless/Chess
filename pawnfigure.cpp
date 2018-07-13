#include "pawnfigure.h"
#include <QBrush>

PawnFigure::PawnFigure(figureColors type)
{
    setColor(type);
    this->setRect(0, 0, 100, 100);

    if (isWhite())
    {
        this->setBrush(QPixmap(":/figures images/pawn_white.png").scaledToHeight(100).scaledToWidth(100));
    }
    else
    {
        this->setBrush(QPixmap(":/figures images/pawn_black2.png").scaledToHeight(100).scaledToWidth(100));
    }
}

bool PawnFigure::moveIsValid()
{
    //position does not change
    if (this->x() == previousPosition.first &&
            this->y() == previousPosition.second)
        return true;

    int offset;
    int begginingOffset = 0;

    isWhite() ? offset = 100 : offset = -100;
    isItBegginingOfGame() ? begginingOffset = offset : begginingOffset = 0;

    if (isItPossibleToBeat())
        if (this->x() == previousPosition.first + offset ||
                (this->x() == previousPosition.first - offset &&
                 this->y() == previousPosition.second - offset))
        {
            beggining = false;
            return true;
        }
        else
        {
            qDebug() << "There is nothing to beat";
            return false;
        }
    else if (this->x() == previousPosition.first &&
              (this->y() == previousPosition.second - offset ||
              (this->y() == previousPosition.second - offset - begginingOffset)))
        {
            beggining = false;
            return true;
        }

//    if (thereIsNoOtherPieceOnField())
//    {
//        //implement sth
//        //probably needs to connect field and pawn
//    }

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
