#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <memory>

using vecOfPairs = std::vector<std::pair<int, int>>;

enum MODE { clicked, unclicked };
enum class figureColors { white, black };

class AbstractFigure : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    MODE mode = unclicked;
    bool possible_to_click = false;
    bool check_ = false;
    vecOfPairs dangeredFields_;
protected:
    bool occupancy = false;
    bool blocked_by_piece = false;
    bool possible_to_beat = false;
public:
    explicit AbstractFigure(QObject *parent = nullptr);
    int rank() { return int(x()); }    // col
    int file() { return int(y()); }    // row
    std::pair<int, int> previousPosition;   //col, row
    figureColors color;
    bool never_moved = true;
    void mousePressEvent(QGraphicsSceneMouseEvent* = nullptr);
    void changeStateOfPreviousPosition(int x, int y);
    void changePossibilityToClick(bool possibility);
    bool isWhite() { return color == figureColors::white; }
    bool isCheck() { return check_; }
    virtual bool dupa(int col, int row) = 0;
    virtual bool moveIsValid() = 0;
    virtual bool isItPossibleToBeat() = 0;
    virtual vecOfPairs dangeredPositions() = 0;
signals:
    void propagateInfoOfAbilityToMove(AbstractFigure* figure);
    void propagateInfoOfDisabilityToMove(AbstractFigure* figure);
    void disableFiguresPickUp(bool state, figureColors color);
    void checkIfOtherFigureHasSamePosition(int col, int row, figureColors color);
    void checkIfThereIsSomethingOnMyWay(int col, int row);
    void checkIfThereIsSomethingOnMyWay(int col, int row, figureColors color);
    void beatFigure(int col, int row, figureColors color);
    void castling(int rookCol, int rookRow, QString direction);
    void castlingBlocker(figureColors color);
    void addDangeredFields();
public slots:
    void setPosition(int col, int row);
    void canBeat(bool beat, int col, int row);
    void fieldIsOccupied(bool occupied);
    void thereIsSomethingOnTheWay(bool blocked);
    void markCheck(bool check, figureColors color);
};

#endif // ABSTRACTFIGURE_H
