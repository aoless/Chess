#include "board.h"
#include "mainwindow.h"
#include <QDebug>
#include <QString>
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

//    addPawnsToBoard(scene, figures["Pawn"]);
    addBishopsToBoard(scene, figures["Bishop"]);
    addKnightsToBoard(scene, figures["Knight"]);
    addRooksToBoard(scene, figures["Rook"]);
//    addQueenToBoard(scene, figures["Queen"]);
    addKingToBoard(scene, figures["King"]);
}

void Board::addPawnsToBoard(QGraphicsScene* scene, const AbstractFigureUniqueVec& pawns)
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

void Board::addBishopsToBoard(QGraphicsScene* scene, const AbstractFigureUniqueVec& bishops)
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

void Board::addKnightsToBoard(QGraphicsScene *scene, const AbstractFigureUniqueVec& knights)
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

void Board::addRooksToBoard(QGraphicsScene *scene, const AbstractFigureUniqueVec& rooks)
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

void Board::addQueenToBoard(QGraphicsScene *scene, const AbstractFigureUniqueVec& queens)
{
    qreal colNumber = 300;
    qreal rowNumber;

    for (auto& queen : queens)
    {
        queen->isWhite() ? rowNumber = 700 : rowNumber = 0;
        setUpFigureOnScene(scene, queen.get(), std::make_pair(colNumber, rowNumber));
    }
}

void Board::addKingToBoard(QGraphicsScene *scene, const AbstractFigureUniqueVec& kings)
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
    connect(figure, AbstractFigure::propagateInfoOfAbilityToMove, this, enableToMoveFigure);
    connect(figure, AbstractFigure::propagateInfoOfDisabilityToMove, this, refuseToMoveFigure);
    connect(figure, AbstractFigure::disableFiguresPickUp, this, disableFiguresPickUp);
    connect(figure, AbstractFigure::checkIfOtherFigureHasSamePosition, this, checkIfThereIsFewFiguresOnSameField);
    connect(figure, AbstractFigure::checkIfThereIsSomethingOnMyWay, this, checkIfThereIsFewFiguresOnSameField);
    connect(figure, AbstractFigure::beatFigure, this, removePiece);
    connect(figure, AbstractFigure::castling, this, castlingHandler);
    connect(figure, AbstractFigure::castlingBlocker, this, disableCasting);
    connect(this, fieldIsOccupied, figure, AbstractFigure::fieldIsOccupied);
    connect(this, thereIsSomethingOnTheWay, figure, AbstractFigure::thereIsSomethingOnTheWay);
    connect(this, canBeat, figure, AbstractFigure::canBeat);
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

void Board::disableFiguresPickUp(bool state, figureColors color)
{
    for (const auto& piece : figures)
        for (const auto& p : piece.second)
            if (p->color == color)
                p->changePossibilityToClick(state);
            else
                p->changePossibilityToClick(!state);
}

void Board::castlingHandler(int rookCol, int rookRow, QString direction)
{
    qDebug() << rookCol << " " << rookRow;
    int offset;

    if (direction == "left")
        offset = -200;
    else if (direction == "right")
        offset = 200;

    for (const auto& piece : figures)
        for (const auto& p : piece.second)
        {
            if (p->ranks() == rookCol && p->files() == rookRow && p->neverMoved)
            {
                p->setPosition(rookCol + offset, rookRow);
                p->changeStateOfPreviousPosition(rookCol + offset, rookRow);
            }
        }
}

void Board::disableCasting(figureColors color)
{
    for (const auto& piece : figures)
        for (const auto& p : piece.second)
        {
            if (p->color == color && piece.first == "King")
                p->neverMoved = false;
        }
}

void Board::checkIfThereIsFewFiguresOnSameField(int col, int row, figureColors color)
{
    int counter = 0;
    for (auto& piece : figures)
    {
        for (auto& p : piece.second)
        {
            if (p->ranks() == col && p->files() == row)
            {
                counter++;
                if (p->color != color && piece.first != "King")
                    emit canBeat(true);
            }
        }
    }

    qDebug() << "counter: " << counter;
    emit fieldIsOccupied(counter > 1);
    emit thereIsSomethingOnTheWay(counter == 1);

}

void Board::removePiece(int col, int row, figureColors color)
{
    for (auto& piece : figures)
    {
        auto& vec = piece.second;

        auto object = std::find_if(vec.begin(), vec.end(), [&](std::unique_ptr<AbstractFigure>& obj){
            return (obj->ranks() == col && obj->files() == row && obj->color != color); });

        if (object != vec.end())
        {
            vec.erase(std::remove(vec.begin(), vec.end(), *object));
            break;
        }
    }
}
