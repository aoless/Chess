#include "board.h"
#include "mainwindow.h"
#include <QDebug>
#include "pawnfigure.h"
#include "bishopfigure.h"
#include "knightfigure.h"
#include "rookfigure.h"
#include "queenfigure.h"
#include "kingfigure.h"

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

Field *Board::getField(int col, int row)
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
    // QObject class has deleted move constructor, that's why we use new instead make_shared<>
    switch(type)
    {
    case pawn:
        figures["Pawn"].emplace_back(new PawnFigure(color));
        break;
    case bishop:
        figures["Bishop"].emplace_back(new BishopFigure(color));
        break;
    case knight:
        figures["Knight"].emplace_back(new KnightFigure(color));
        break;
    case rook:
        figures["Rook"].emplace_back(new RookFigure(color));
        break;
    case queen:
        figures["Queen"].emplace_back(new QueenFigure(color));
        break;
    case king:
        figures["King"].emplace_back(new KingFigure(color));
        break;
    }
}

void Board::createFiguresAndAddPiecesToBoard(QGraphicsScene* scene)
{
    for (int i = 0; i < 8; i++)
        createFigure(pawn, figureColors::black);

    for (int i = 0; i < 8; i++)
        createFigure(pawn, figureColors::white);

    for (int i = 0; i < 2; i++)
        createFigure(bishop, figureColors::black);

    for (int i = 0; i < 2; i++)
        createFigure(bishop, figureColors::white);

    for (int i = 0; i < 2; i++)
        createFigure(knight, figureColors::black);

    for (int i = 0; i < 2; i++)
        createFigure(knight, figureColors::white);

    for (int i = 0; i < 2; i++)
        createFigure(rook, figureColors::black);

    for (int i = 0; i < 2; i++)
        createFigure(rook, figureColors::white);

    for (int i = 0; i < 1; i++)
        createFigure(queen, figureColors::black);

    for (int i = 0; i < 1; i++)
        createFigure(queen, figureColors::white);

    for (int i = 0; i < 1; i++)
        createFigure(king, figureColors::black);

    for (int i = 0; i < 1; i++)
        createFigure(king, figureColors::white);

    addPawnsToBoard(scene, figures["Pawn"]);
    addBishopsToBoard(scene, figures["Bishop"]);
    addKnightsToBoard(scene, figures["Knight"]);
    addRooksToBoard(scene, figures["Rook"]);
    addQueenToBoard(scene, figures["Queen"]);
    addKingToBoard(scene, figures["King"]);
}

void Board::addPawnsToBoard(QGraphicsScene* scene, const AbstractFigureSharedVec& pawns)
{
    int colNumber = 0;
    int rowNumber;

    for (auto& pawn : pawns)
    {
        pawn->isWhite() ? rowNumber = 600 : rowNumber = 100;
        setUpFigureOnScene(scene, pawn.get(), std::make_pair(colNumber, rowNumber));
        colNumber += 100;
        if (colNumber == 800)
            colNumber = 0;
    }
}

void Board::addBishopsToBoard(QGraphicsScene* scene, const AbstractFigureSharedVec& bishops)
{
    qreal colNumber = 200;
    qreal rowNumber;

    for (auto& bishop : bishops)
    {
        bishop->isWhite() ? rowNumber = 700 : rowNumber = 0;
        setUpFigureOnScene(scene, bishop.get(), std::make_pair(colNumber, rowNumber));
        colNumber += 300;
        if (colNumber > 500)
            colNumber = 200;
    }
}

void Board::addKnightsToBoard(QGraphicsScene *scene, const AbstractFigureSharedVec& knights)
{
    qreal colNumber = 100;
    qreal rowNumber;

    for (auto& knight : knights)
    {
        knight->isWhite() ? rowNumber = 700 : rowNumber = 0;
        setUpFigureOnScene(scene, knight.get(), std::make_pair(colNumber, rowNumber));
        colNumber += 500;
        if (colNumber > 600)
            colNumber = 100;
    }
}

void Board::addRooksToBoard(QGraphicsScene *scene, const AbstractFigureSharedVec& rooks)
{
    qreal colNumber = 0;
    qreal rowNumber;

    for (auto& rook : rooks)
    {
        rook->isWhite() ? rowNumber = 700 : rowNumber = 0;
        setUpFigureOnScene(scene, rook.get(), std::make_pair(colNumber, rowNumber));
        colNumber += 700;
        if (colNumber > 700)
            colNumber = 0;
    }
}

void Board::addQueenToBoard(QGraphicsScene *scene, const AbstractFigureSharedVec& queens)
{
    qreal colNumber = 300;
    qreal rowNumber;

    for (auto& queen : queens)
    {
        queen->isWhite() ? rowNumber = 700 : rowNumber = 0;
        setUpFigureOnScene(scene, queen.get(), std::make_pair(colNumber, rowNumber));
    }
}

void Board::addKingToBoard(QGraphicsScene *scene, const AbstractFigureSharedVec& kings)
{
    qreal colNumber = 400;
    qreal rowNumber;

    for (auto& king : kings)
    {
        king->isWhite() ? rowNumber = 700 : rowNumber = 0;
        setUpFigureOnScene(scene, king.get(), std::make_pair(colNumber, rowNumber));
    }
}

void Board::setUpFigureOnScene(QGraphicsScene* scene, AbstractFigure* figure, std::pair<qreal, qreal> position)
{
    scene->addItem(figure);
    figure->setPosition(int(position.first), int(position.second));
    figure->changeStateOfPreviousPosition(int(position.first), int(position.second));
    connecter(figure);
}

void Board::connecter(const AbstractFigure* figure)
{
    connect(figure, AbstractFigure::propagateInfoOfAbilityToMove, this, Board::enableToMoveFigure);
    connect(figure, AbstractFigure::propagateInfoOfDisabilityToMove, this, Board::refuseToMoveFigure);
    connect(figure, AbstractFigure::unableToPickOtherFigures, this, Board::changeMovableStateOfAllFigures);
    connect(figure, AbstractFigure::checkIfOtherFigureHasSamePosition,
        this, Board::checkIfThereIsFewFiguresOnSameField);
    connect(figure, AbstractFigure::checkIfThereIsSomethingOnMyWay,
        this, Board::checkIfThereIsFewFiguresOnSameField);
    connect(this, Board::fieldIsOccupied, figure, AbstractFigure::fieldIsOccupied);
    connect(this, Board::thereIsSomethingOnTheWay, figure, AbstractFigure::thereIsSomethingOnTheWay);
}

void Board::enableToMoveFigure(AbstractFigure* figure)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            connect(fields[i][j], Field::sendCoordinates, figure, AbstractFigure::setPosition);
}

void Board::refuseToMoveFigure(AbstractFigure* figure)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            disconnect(fields[i][j], Field::sendCoordinates, figure, AbstractFigure::setPosition);
}

void Board::changeMovableStateOfAllFigures(bool state)
{
    for (const auto& piece : figures)
        for (const auto& p : piece.second)
            p->changePossibilityToClick(state);
}

void Board::checkIfThereIsFewFiguresOnSameField(int col, int row)
{
    int counter = 0;
    for (const auto& piece : figures)
        for (const auto& p : piece.second)
            if (int(p->x()) == col && int(p->y()) == row)
                counter++;

    qDebug() << counter;
    if (counter > 1)
        emit fieldIsOccupied(true);
    else
        emit fieldIsOccupied(false);

    if(counter == 1)
        emit thereIsSomethingOnTheWay(true);
    else
        emit thereIsSomethingOnTheWay(false);
}
