#ifndef CHECKHANDLER_H
#define CHECKHANDLER_H

#include <QObject>
#include <vector>

using vecOfPairs = std::vector<std::pair<int, int>>;

class CheckHandler : public QObject
{
    Q_OBJECT
private:
     vecOfPairs dangeredPositions;
public:
    explicit CheckHandler();

signals:

public slots:
    void fillDangeredPositions(vecOfPairs);
};

#endif // CHECKHANDLER_H
