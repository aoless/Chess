#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QRect>
#include <array>
#include <map>
#include "field.h"
#include "abstractfigure.h"

using AbstractFigureUniqueVec = std::vector<std::unique_ptr<AbstractFigure>>;
using squareMatrix = std::array<std::array<Field*, 8>, 8>;

enum figureTypes { pawn, knight, bishop, rook, queen, king };

class Board: public QObject
{
    Q_OBJECT
private:
    squareMatrix fields;
    std::map<std::string, AbstractFigureUniqueVec> figures;
public:
    Board();
    ~Board();
    QGraphicsRectItem *getSingleSquare(int row, int col);
    Field *getField(int col, int row);
    void drawChessBoard(QGraphicsScene* scene);
    void createFigure(figureTypes type, figureColors color);
    void createFiguresAndAddPiecesToBoard(QGraphicsScene*);
    void addPawnsToBoard(QGraphicsScene*, const AbstractFigureUniqueVec&);
    void addBishopsToBoard(QGraphicsScene*, const AbstractFigureUniqueVec&);
    void addKnightsToBoard(QGraphicsScene*, const AbstractFigureUniqueVec&);
    void addRooksToBoard(QGraphicsScene*, const AbstractFigureUniqueVec&);
    void addQueenToBoard(QGraphicsScene*, const AbstractFigureUniqueVec&);
    void addKingToBoard(QGraphicsScene*, const AbstractFigureUniqueVec&);
    void connecter(const AbstractFigure*);
    void setUpFigureOnScene(QGraphicsScene*, AbstractFigure*, std::pair<qreal, qreal>);
    void checkIfThereIsFewFiguresOnSameField(int col, int row, figureColors color);
    void removePiece(int col, int row, figureColors color);
public slots:
    void enableToMoveFigure(AbstractFigure* figure);
    void refuseToMoveFigure(AbstractFigure* figure);
    void disableFiguresPickUp(bool state, figureColors color);
signals:
    void fieldIsOccupied(bool occupied);
    void thereIsSomethingOnTheWay(bool blockedByPiece);
    void canBeat(bool possibility);
};

#endif // BOARD_H
