#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include <QObject>
#include <QGraphicsRectItem>

class AbstractFigure : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit AbstractFigure(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ABSTRACTFIGURE_H
