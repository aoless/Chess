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
    bool possible_to_click = false;
protected:
    std::pair<int, int> previousPosition;   //col, row
    bool occupancy;
    bool blocked_by_piece;
    bool possible_to_beat;
public:
    explicit AbstractFigure(QObject *parent = nullptr);
    figureColors color;
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void changeStateOfPreviousPosition(int x, int y);
    void changePossibilityToClick(bool possibility);
    void fieldIsOccupied(bool occupied);
    void thereIsSomethingOnTheWay(bool blocked);
    bool isWhite() { return color == figureColors::white; }
    int horizontalPos() { return int(x()); }
    int verticalPos() { return int(y()); }
    virtual bool moveIsValid() = 0;
    virtual bool isItPossibleToBeat() = 0;
signals:
    void propagateInfoOfAbilityToMove(AbstractFigure* figure);
    void propagateInfoOfDisabilityToMove(AbstractFigure* figure);
    void disableFiguresPickUp(bool state, figureColors color);
    void checkIfOtherFigureHasSamePosition(int col, int row, figureColors color);
    void checkIfThereIsSomethingOnMyWay(int col, int row, figureColors color);
public slots:
    void setPosition(int col, int row);
};

#endif // ABSTRACTFIGURE_H
