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
    void addPawnsToBoard(QGraphicsScene*, AbstractFigureSharedVec&);
    void addBishopsToBoard(QGraphicsScene*, AbstractFigureSharedVec&);
    void addRooksToBoard(QGraphicsScene*, AbstractFigureSharedVec&);
    void connecter(AbstractFigure*);
    void setUpFigureOnScene(QGraphicsScene*, AbstractFigure*, std::pair<qreal, qreal>);
public slots:
    void enableToMoveFigure(AbstractFigure* figure);
    void refuseToMoveFigure(AbstractFigure* figure);
    void changeMovableStateOfAllFigures(bool state);
};

#endif // BOARD_H
