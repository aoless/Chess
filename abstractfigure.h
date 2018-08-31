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
    std::pair<qreal, qreal> previousPosition;   //col, row
    bool occupancy;
public:
    explicit AbstractFigure(QObject *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    virtual bool moveIsValid() = 0;
    virtual bool isItPossibleToBeat() = 0;
    virtual bool thereIsNoOtherPieceOnField() = 0;
    void changeStateOfPreviousPosition(qreal x, qreal y);
    bool isWhite();
    void setColor(figureColors c);
    void changePossibilityToClick(bool possibility);
    void fieldIsOccupied(bool occupied);

signals:
    void propagateInfoOfAbilityToMove(AbstractFigure* figure);
    void propagateInfoOfDisabilityToMove(AbstractFigure* figure);
    void unableToPickOtherFigures(bool state);
    void assignMeSomePlacePlease(AbstractFigure* figurePtr);
    bool checkIfOtherFigureHasSamePosition(qreal col, qreal row);

public slots:
    void setPosition(qreal col, qreal row);
};

#endif // ABSTRACTFIGURE_H
