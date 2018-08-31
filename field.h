#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <utility>
#include <QGraphicsSceneEvent>
#include <QMouseEvent>
#include "abstractfigure.h"

class Field : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    enum VARIANT { white, black };
    const int size = 100;
    std::pair<int, int> position;
    QPixmap fieldColor;
    std::shared_ptr<AbstractFigure> figure;
protected:
    bool hasFigure = false;
public:
    void setVariant(VARIANT color);
    QGraphicsRectItem* drawSquare() { return this; }
    Field(int row, int col);
    ~Field() { }
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
signals:
    void sendCoordinates(qreal x, qreal y);
    void showCoordinates(QString c);
};

#endif // FIELD_H
