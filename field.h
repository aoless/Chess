#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPixmap>
#include <utility>

class Field : public QObject
{
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
};

#endif // FIELD_H
