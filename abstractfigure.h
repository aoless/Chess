#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <memory>

enum MODE { clicked, unclicked };
enum class figureColors { white, black };

class AbstractFigure : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    MODE mode = unclicked;
    figureColors color;
    bool possible_to_click = true;
protected:
    std::pair<int, int> previousPosition;   //col, row
    bool occupancy;
    bool blockedByPiece;
public:
    explicit AbstractFigure(QObject *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    virtual bool moveIsValid() = 0;
    virtual bool isItPossibleToBeat() = 0;
    void changeStateOfPreviousPosition(int x, int y);
    bool isWhite();
    void setColor(figureColors c);
    void changePossibilityToClick(bool possibility);
    void fieldIsOccupied(bool occupied);
    void thereIsSomethingOnTheWay(bool blocked);
signals:
    void propagateInfoOfAbilityToMove(AbstractFigure* figure);
    void propagateInfoOfDisabilityToMove(AbstractFigure* figure);
    void unableToPickOtherFigures(bool state);
    void checkIfOtherFigureHasSamePosition(int col, int row);
    void checkIfThereIsSomethingOnMyWay(int col, int row);
public slots:
    void setPosition(int col, int row);
};

#endif // ABSTRACTFIGURE_H
