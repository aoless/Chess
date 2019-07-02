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

#include <QTime>
#include <QCoreApplication>

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

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

void Board::createFigure(figureTypes type, figureColors color) // can be factory method!
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
    connect(figure, SIGNAL(propagateInfoOfAbilityToMove(AbstractFigure*)), this, SLOT(enableToMoveFigure(AbstractFigure*)));
    connect(figure, SIGNAL(propagateInfoOfDisabilityToMove(AbstractFigure*)), this, SLOT(refuseToMoveFigure(AbstractFigure*)));
    connect(figure, SIGNAL(disableFiguresPickUp(bool,figureColors)), this, SLOT(disableFiguresPickUp(bool,figureColors)));
    connect(figure, SIGNAL(checkIfOtherFigureHasSamePosition(int,int,figureColors)), this, SLOT(checkIfThereIsFewFiguresOnSameField(int,int,figureColors)));
    connect(figure, SIGNAL(checkIfThereIsSomethingOnMyWay(int,int)), this, SLOT(propagateSignalUnitlItMeetsFigure(int,int)));
    connect(figure, SIGNAL(checkIfThereIsSomethingOnMyWay(int,int,figureColors)), this, SLOT(checkIfThereIsFewFiguresOnSameField(int,int,figureColors)));
    connect(figure, SIGNAL(beatFigure(int,int,figureColors)), this, SLOT(removePiece(int,int,figureColors)));
    connect(figure, SIGNAL(castling(int,int,QString)), this, SLOT(castlingHandler(int,int,QString)));
    connect(figure, SIGNAL(castlingBlocker(figureColors)), this, SLOT(disableCasting(figureColors)));
    connect(figure, SIGNAL(addDangeredFields()), this, SLOT(addDangeredFields()));
    connect(this, SIGNAL(fieldIsOccupied(bool)), figure, SLOT(fieldIsOccupied(bool)));
    connect(this, SIGNAL(thereIsSomethingOnTheWay(bool)), figure, SLOT(thereIsSomethingOnTheWay(bool)));
    connect(this, SIGNAL(canBeat(bool, int, int)), figure, SLOT(canBeat(bool, int, int)));
    connect(this, SIGNAL(isCheck(bool, figureColors)), figure, SLOT(markCheck(bool, figureColors)));
}

void Board::enableToMoveFigure(AbstractFigure* figure)
{
    for (unsigned long long i = 0; i < 8; i++)
        for (unsigned long long j = 0; j < 8; j++)
            connect(fields[i][j], SIGNAL(sendCoordinates(int,int)), figure, SLOT(setPosition(int, int)));
}

void Board::refuseToMoveFigure(AbstractFigure* figure)
{
    for (unsigned long long i = 0; i < 8; i++)
        for (unsigned long long j = 0; j < 8; j++)
            disconnect(fields[i][j], SIGNAL(sendCoordinates(int,int)), figure, SLOT(setPosition(int, int)));
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
    int offset{};

    if (direction == "left")
        offset = -200;
    else if (direction == "right")
        offset = 200;

    for (const auto& piece : figures)
        for (const auto& p : piece.second)
        {
            if (p->rank() == rookCol && p->file() == rookRow && p->never_moved)
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
                p->never_moved = false;
        }
}

void Board::addDangeredFields()
{
    vecOfPairs temp;
    whiteAttackingFields_.clear();
    blackAttackingFields_.clear();
    for (const auto& piece : figures)
    {
        for (const auto& p : piece.second)
        {
            temp = p->dangeredPositions();
            p->isWhite() ? whiteAttackingFields_.insert(whiteAttackingFields_.end(), temp.begin(), temp.end()) :
                blackAttackingFields_.insert(blackAttackingFields_.end(), temp.begin(), temp.end());
        }
    }

    lookForAKingAndCheckIfHeIsInCheck();
}

void Board::lookForAKingAndCheckIfHeIsInCheck()
{
    vecOfPairs::iterator it;
    for (auto& piece : figures)
    {
        for (auto& p : piece.second)
        {
            if (piece.first == "King")
            {
                switch (p->color)
                {
                case figureColors::white:
                    it = std::find(blackAttackingFields_.begin(), blackAttackingFields_.end(),
                         std::make_pair(p->rank(), p->file()));
                    if (it != blackAttackingFields_.end())
                    {
                        qDebug() << "WHITE in CHECK!";
                        chekIfCheckMate(p.get());
                        emit isCheck(true, figureColors::white);
                    }
                    else
                    {
                        emit isCheck(false, figureColors::white);
                    }
                    break;
                case figureColors::black:
                    it = std::find(whiteAttackingFields_.begin(), whiteAttackingFields_.end(),
                         std::make_pair(p->rank(), p->file()));
                    if (it != whiteAttackingFields_.end())
                    {
                        qDebug() << "BLACK in CHECK!";
                        chekIfCheckMate(p.get());
                        emit isCheck(true, figureColors::black);
                    }
                    else
                    {
                        emit isCheck(false, figureColors::black);
                    }
                    break;
                }
            }
        }
    }
}

void Board::chekIfCheckMate(AbstractFigure* king)
{
    qDebug() << "===============";

    vecOfPairs possibleDirections = { std::make_pair(100, 0), std::make_pair(100, 100),
                                      std::make_pair(0, 100), std::make_pair(-100, 100),
                                      std::make_pair(-100, 0), std::make_pair(-100, -100),
                                      std::make_pair(0, -100), std::make_pair(100, -100) };

    int orginalRank = king->rank();
    int orginalFile = king->file();

    vecOfPairs attackingFields;
    vecOfPairs safeMoves;
    vecOfPairs kingSavingPositions;
    vecOfPairs evenMoreSaving;

    if (king->isWhite())
    {
        attackingFields = blackAttackingFields_;
    }
    else
    {
        attackingFields = whiteAttackingFields_;
    }

    for (const auto& direction: possibleDirections)
    {
        int newRank = orginalRank + direction.first;
        int newFile = orginalFile + direction.second;

        if (newRank < 0 || newRank > 700 || newFile < 0 || newFile > 700)
            continue;

        if (king->moveIsValidWrapper(newRank, newFile))
            safeMoves.push_back(std::make_pair(newRank, newFile));
    }


    for (auto safeMove : safeMoves)
    {
        if (std::find(attackingFields.begin(), attackingFields.end(), safeMove) == attackingFields.end())
        {
            qDebug() << "Pole " << safeMove.first << ", " << safeMove.second << " nie jest niczym zagrożone";
            // check if any piece can go to that field
        }
        else
        {
            qDebug() << "Pole " << safeMove.first << ", " << safeMove.second << " odpada";
        }
    }


//                for (auto t : temp)
//                {
//                    if (p->moveIsValidWrapper(t.first, t.second) && // jesli ruch jest mozliwy
//                            std::find(attackingFields.begin(), attackingFields.end(),
//                                std::pair<int, int>(t.first, t.second)) != attackingFields.end())   // i znajduje sie wsrod zagrozonych pozycji
//                        kingSavingPositions.emplace_back(t.first, t.second);    // moze uratowac krola
//                }

    for (auto kSP : kingSavingPositions)
    {
        vecOfPairs::iterator it;
        it = std::find(whiteAttackingFields_.begin(), whiteAttackingFields_.end(), std::make_pair(kSP.first, kSP.second));
        if (it != whiteAttackingFields_.end())
        {
            evenMoreSaving.emplace_back(kSP.first, kSP.second);
        }
    }

//    for badMoves

//    if (std::find(kingSavingPositions.begin(), kingSavingPositions.end(), b) != kingSavingPositions.end())
//    {
//        evenMoreSaving.emplace_back(safeMove);
//    }
    for (auto& eMS : evenMoreSaving)
    {
        qDebug() << "King can be saved by: " << eMS.first << ", " << eMS.second;
    }
}

void Board::propagateSignalUnitlItMeetsFigure(int col, int row)
{
    int counter = 0;
    for (auto& piece : figures)
    {
        for (auto& p : piece.second)
        {
            if (p->rank() == col && p->file() == row)
            {
                counter++;
            }
        }
    }

    emit fieldIsOccupied(counter > 1);
    emit thereIsSomethingOnTheWay(counter == 1);
}


void Board::checkIfThereIsFewFiguresOnSameField(int col, int row, figureColors color)
{
    int counter = 0;
    for (auto& piece : figures)
    {
        for (auto& p : piece.second)
        {
            if (p->rank() == col && p->file() == row)   // related to figure position
            {
                counter++;
                if (p->color != color && piece.first != "King")
                {
                    if (!p->isCheck())
                        emit canBeat(true, col, row);
                }
            }
        }
    }

    emit fieldIsOccupied(counter > 1);
    emit thereIsSomethingOnTheWay(counter == 1);

}

void Board::removePiece(int col, int row, figureColors color)
{
    for (auto& piece : figures)
    {
        auto& vec = piece.second;

        auto object = std::find_if(vec.begin(), vec.end(), [&](std::unique_ptr<AbstractFigure>& obj){
            return (obj->rank() == col && obj->file() == row && obj->color != color); });

        if (object != vec.end())
        {
            vec.erase(std::remove(vec.begin(), vec.end(), *object));
            break;
        }
    }
}
