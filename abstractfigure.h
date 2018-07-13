#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

enum MODE { clicked, unclicked };
enum figureColors { white, black };

class AbstractFigure : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    qreal row, col;
    MODE mode = unclicked;
    figureColors color;
    bool possible_to_click = true;
protected:
    std::pair<qreal, qreal> previousPosition;   //col, row
public:
    explicit AbstractFigure(QObject *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    virtual bool moveIsValid() = 0;
    virtual bool isItPossibleToBeat() = 0;
    void changeStateOfPreviousPosition(qreal x, qreal y);
    bool isWhite();
    void setColor(figureColors c);
    void changePossibilityToClick(bool p);

signals:
    void connectThisShit(AbstractFigure* figure);
    void disconnectThisShit(AbstractFigure* figure);
    void unableToPickOtherFigures(bool state);

public slots:
    void setPosition(qreal x, qreal y);
};

#endif // ABSTRACTFIGURE_H
