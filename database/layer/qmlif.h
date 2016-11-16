#ifndef QMLIF_H
#define QMLIF_H
#include <QObject>
#include <QDebug>
#include "../tester/testflexible.h"
class QMLif : public QObject
{
    Q_OBJECT
signals:
    void clicked();
public slots:
    QString doSomething()
    {
        testflexible t;
        t.begintest();
        return "test flexible table end";
    }

public:
    QMLif();
};

#endif // QMLIF_H
