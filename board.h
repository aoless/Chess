#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QRect>
#include <array>
#include <memory>
#include <map>
#include "field.h"
#include "abstractfigure.h"

using AbstractFigureSharedVec = std::vector<std::shared_ptr<AbstractFigure>>;
using squareMatrix = std::array<std::array<Field*, 8>, 8>;

enum figureTypes { pawn, knight, bishop, rook, queen, king };

class Board: public QObject
{
    Q_OBJECT
private:
    squareMatrix fields;
    std::map<std::string, AbstractFigureSharedVec> figures;
public:
    Board();
    ~Board();
    QGraphicsRectItem *getSingleSquare(int row, int col);
    Field *getField(int row, int col);
    void drawChessBoard(QGraphicsScene* scene);
    void createFigure(figureTypes type, figureColors color);
    void createFiguresAndAddPiecesToBoard(QGraphicsScene*);
    void addPawnsToBoard(QGraphicsScene*, const AbstractFigureSharedVec&);
    void addBishopsToBoard(QGraphicsScene*, const AbstractFigureSharedVec&);
    void addKnightsToBoard(QGraphicsScene*, const AbstractFigureSharedVec&);
    void addRooksToBoard(QGraphicsScene*, const AbstractFigureSharedVec&);
    void addQueenToBoard(QGraphicsScene*, const AbstractFigureSharedVec&);
    void addKingToBoard(QGraphicsScene*, const AbstractFigureSharedVec&);
    void connecter(const AbstractFigure*);
    void setUpFigureOnScene(QGraphicsScene*, AbstractFigure*, std::pair<qreal, qreal>);
    void checkIfThereIsFewFiguresOnSameField(qreal col, qreal row);
public slots:
    void enableToMoveFigure(AbstractFigure* figure);
    void refuseToMoveFigure(AbstractFigure* figure);
    void changeMovableStateOfAllFigures(bool state);
signals:
    void fieldIsOccupied(bool occupied);
};

#endif // BOARD_H
