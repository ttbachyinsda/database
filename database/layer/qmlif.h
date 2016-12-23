#ifndef QMLIF_H
#define QMLIF_H
#include "../tester/testflexible.h"
#include <QDebug>
#include <QObject>
#include <QThread>
class WorkerThread : public QThread {
    Q_OBJECT
    void run() Q_DECL_OVERRIDE
    {
        QString result = "test flexible table end";
        testflexible t;
        t.begintest();
        emit resultReady(result);
    }
signals:
    void resultReady(const QString& s);
};
class QMLif : public QObject {
    Q_OBJECT
signals:
    void clicked();
    void resultReady(const QString& s);
public slots:
    void doSomething()
    {
        WorkerThread* workerThread = new WorkerThread();
        connect(workerThread, SIGNAL(resultReady(const QString&)), this, SLOT(done(const QString&)));
        //connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
        workerThread->start();
    }
    void done(const QString& s)
    {
        i++;
        text = s;
        emit resultReady(s);
    }
    QString gettext()
    {
        return this->text + QString::number(i, 10);
    }
    void receivedastring(const QString& s)
    {
        string t = s.toStdString();
        cout << t << endl;
    }

public:
    QString text;
    int i;
    QMLif();
};

#endif
