#include "board.h"
#include "mainwindow.h"
#include <QDebug>
#include <typeinfo>
#include "pawnfigure.h"
#include "bishopfigure.h"
#include "rookfigure.h"

Board::Board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            fields[i][j] = new Field(i, j);
}

Board::~Board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete fields[i][j];
}

QGraphicsRectItem * Board::getSingleSquare(int col, int row)
{
    return fields[col][row]->drawSquare();
}

Field *Board::getField(int row, int col)
{
    return fields[col][row];
}

void Board::drawChessBoard(QGraphicsScene *scene)
{
    qreal x = 0; qreal y = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scene->addItem(getSingleSquare(i, j));
            getSingleSquare(i, j)->setPos(x, y);
            x += 100;
        }
        y += 100;
        x = 0;
    }
}

void Board::createFigure(figureTypes type, figureColors color)
{
    switch(type)
    {
    case pawn:
        figures["Pawn"].emplace_back(new PawnFigure(color));
        break;
    case bishop:
        figures["Bishop"].emplace_back(new BishopFigure(color));
        break;
    case rook:
        figures["Rook"].emplace_back(new RookFigure(color));
        break;
    }
}

void Board::createFiguresAndAddPiecesToBoard(QGraphicsScene* scene)
{
    for (int i = 0; i < 8; i++)
        createFigure(pawn, black);

    for (int i = 0; i < 8; i++)
        createFigure(pawn, white);

    for (int i = 0; i < 2; i++)
       createFigure(bishop, black);

    for (int i = 0; i < 2; i++)
        createFigure(rook, black);

    addPawnsToBoard(scene, figures["Pawn"]);
    addBishopsToBoard(scene, figures["Bishop"]);
    addRooksToBoard(scene, figures["Rook"]);
}

void Board::addPawnsToBoard(QGraphicsScene* scene, AbstractFigureSharedVec& pawns)
{
    qreal colNumber = 0;
    qreal rowNumber;

    for (auto& pawn : pawns)
    {
        pawn->isWhite() ? rowNumber = 600 : rowNumber = 100;
        setUpFigureOnScene(scene, pawn.get(), std::make_pair(colNumber, rowNumber));
        colNumber += 100;
        if (colNumber == 800)
            colNumber = 0;
    }
}

void Board::addBishopsToBoard(QGraphicsScene* scene, AbstractFigureSharedVec& bishops)
{
    qreal colNumber = 200;
    qreal rowNumber;

    for (auto& bishop : bishops)
    {
        bishop->isWhite() ? rowNumber = 700 : rowNumber = 0;
        setUpFigureOnScene(scene, bishop.get(), std::make_pair(colNumber, rowNumber));
        colNumber += 300;
    }

}

void Board::addRooksToBoard(QGraphicsScene *scene, AbstractFigureSharedVec& rooks)
{
    qreal colNumber = 0;
    qreal rowNumber;

    for (auto& rook : rooks)
    {
        rook->isWhite() ? rowNumber = 700 : rowNumber = 0;
        setUpFigureOnScene(scene, rook.get(), std::make_pair(colNumber, rowNumber));
        colNumber += 700;
    }
}

void Board::setUpFigureOnScene(QGraphicsScene* scene, AbstractFigure* figure, std::pair<qreal, qreal> position)
{
    scene->addItem(figure);
    figure->setPosition(position.first, position.second);
    figure->changeStateOfPreviousPosition(position.first, position.second);
    connecter(figure);
}

void Board::connecter(AbstractFigure* figure)
{
    connect(figure, AbstractFigure::connectThisShit, this, Board::enableToMoveFigure);
    connect(figure, AbstractFigure::disconnectThisShit, this, Board::refuseToMoveFigure);
    connect(figure, AbstractFigure::unableToPickOtherFigures, this, Board::changeMovableStateOfAllFigures);
}

void Board::enableToMoveFigure(AbstractFigure* figure)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            connect(fields[i][j], Field::sendCoordinates, figure, AbstractFigure::setPosition);
        }
    }
}

void Board::refuseToMoveFigure(AbstractFigure* figure)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            disconnect(fields[i][j], Field::sendCoordinates, figure, AbstractFigure::setPosition);
        }
    }
}

void Board::changeMovableStateOfAllFigures(bool state)
{
    for (auto& f : figures["Pawn"])
    {
        f->changePossibilityToClick(state);
    }

}

