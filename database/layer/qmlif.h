#ifndef QMLIF_H
#define QMLIF_H
#include "../tester/testflexible.h"
#include "../sqlengine/sqldriver.h"
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>
#include <QTextStream>

class WorkerThread : public QThread {
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
signals:
    void resultReady(const QString& s);

public:
    WorkerThread(SQLDriver *driver, const QString command) :
    command(command) {
        this->driver = driver;
    }
    SQLDriver *driver;
    QString command;
};
class QMLif : public QObject {
    Q_OBJECT
signals:
    void clicked();
    void resultReady(const QString& s);
public slots:
    void doSomething(const QString command) {
//        cout << command.toStdString() << endl;
        WorkerThread* workerThread = new WorkerThread(oldDriver, command);
        connect(workerThread, SIGNAL(resultReady(const QString&)), this, SLOT(done(const QString&)));
        //connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
        workerThread->start();
    }
    void done(const QString& s) {
        i++;
        text = s;
        emit resultReady(s);
    }
    QString gettext()
    {
        return this->text;
    }
    void receivedastring(const QString& s)
    {
        string t = s.toStdString();
        cout << t << endl;
    }

public:
    QString text;
    static SQLDriver *oldDriver;
    int i;
    QMLif();

    static string testcss;
};

#endif
