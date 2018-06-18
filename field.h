#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <utility>
#include <QGraphicsSceneEvent>
#include <QMouseEvent>

class Field : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    enum VARIANT { white, black };
    const int size = 100;
    std::pair<int, int> position;
    QGraphicsRectItem * rect;
    QPixmap fieldColor;
public:
    void setVariant(VARIANT color);
    QGraphicsRectItem * drawSquare() { return rect; }
    Field(int row, int col);
    ~Field() { delete rect; }
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
signals:
    void showCoordinates(QString);
};

#endif // FIELD_H
