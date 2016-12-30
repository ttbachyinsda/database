#include "qmlif.h"
#include <fstream>
#include "json.hpp"
#include <QNetworkRequest>
string QMLif::testcss;
SQLDriver QMLif::oldDriver;
SQLResult *QMLif::lastResult = 0;
QQuickItem *QMLif::dbList = 0;

using json = nlohmann::json;
using namespace std;

void WorkerThread::run() {
    QString result = "";
    driver->execute(command.toStdString());
    cout << command.toStdString() << endl;
    cout << driver->hasResult() << endl;
    QTextStream outFile(&result);
    outFile << "<!DOCTYPE html>\n<html>\n<style type=\"text/css\">\n" << QMLif::testcss.c_str() << "</style>\n" << endl;
    if (driver->hasResult()) {
        outFile << "<body>\n<center>\t<table>\n\t\t<caption>Result</caption>\n";
        outFile << "\t\t<thead>\n\t\t\t<tr>" << endl;
        QMLif::lastResult = driver->getResult();
        for (std::string& t : QMLif::lastResult->title) {
            outFile << "\t\t\t\t<th>" << t.c_str() << endl;
        }
        outFile << "\t\t</thead>" << endl;
        outFile << "\t\t<tbody>" << endl;
        int i = 0;
        for (std::vector<std::string>& r : QMLif::lastResult->data) {
            i ++;
            outFile << "\t\t\t<tr>" << endl;
            for (std::string& t : r) {
                outFile << "\t\t\t\t<td>" << t.c_str() << endl;
            }
            if (i > 50)
                break;
        }
        outFile << "\t\t</tbody>" << endl;
        outFile << "\t\t</table>" << endl;
    }
    vector<std::string> msg = driver->getErrorMessages();
    for (int i = 0 ; i < msg.size(); i++)
        outFile << "\t\t<p>" << msg[i].c_str() << "</p>" << "\n";
    msg = driver->getWarningMessages();
    for (int i = 0 ; i < msg.size(); i++)
        outFile << "\t\t<p>" << msg[i].c_str() << "</p>" << "\n";
    outFile << "</center>\t</body>\n</html>" << endl;

    emit resultReady(result);
}

QStringList QMLif::getDBList() {
//    QString result;
    QStringList dataList;
    oldDriver.execute("show databases;");
//    QTextStream outFile(&result);
    if (oldDriver.hasResult()) {
        SQLResult* temp = oldDriver.getResult();
        for (std::vector<std::string>& r : temp->data) {
            dataList.append(QString(r[1].c_str()));
//            result.clear();
        }
    }
    return dataList;
}

QStringList QMLif::getTable(QString name) {
//    QString result;
    QStringList dataList;
    oldDriver.execute("use " + name.toStdString() + ";");
    oldDriver.execute("show tables;");
//    QTextStream outFile(&result);
    if (oldDriver.hasResult()) {
        SQLResult* temp = oldDriver.getResult();
        for (std::vector<std::string>& r : temp->data) {
            dataList.append(QString(r[1].c_str()));
//            result.clear();
        }
    }
    return dataList;
}

QString QMLif::getNextResult() {
    if (counter * 50 + 50 < lastResult->data.size())
        counter++;
    QString result = "";
    QTextStream outFile(&result);
    outFile << "<!DOCTYPE html>\n<html>\n<style type=\"text/css\">\n" << QMLif::testcss.c_str() << "</style>\n" << endl;
    outFile << "<body>\n<center>\t<table>\n\t\t<caption>Result</caption>\n";
    outFile << "\t\t<thead>\n\t\t\t<tr>" << endl;
    for (std::string& t : QMLif::lastResult->title) {
        outFile << "\t\t\t\t<th>" << t.c_str() << endl;
    }
    outFile << "\t\t</thead>" << endl;
    outFile << "\t\t<tbody>" << endl;
    for (int i = counter * 50; i < counter * 50 + 50 && i < lastResult->data.size(); ++i) {
        outFile << "\t\t\t<tr>" << endl;
        for (std::string& t : lastResult->data[i]) {
            outFile << "\t\t\t\t<td>" << t.c_str() << endl;
        }
    }
    outFile << "\t\t</tbody>" << endl;
    outFile << "\t\t</table>" << endl;
    outFile << "</center>\t</body>\n</html>" << endl;
    return result;
}

QString QMLif::getPrevResult() {
    if (counter >= 1)
        counter--;
    QString result = "";
    QTextStream outFile(&result);
    outFile << "<!DOCTYPE html>\n<html>\n<style type=\"text/css\">\n" << QMLif::testcss.c_str() << "</style>\n" << endl;
    outFile << "<body>\n<center>\t<table>\n\t\t<caption>Result</caption>\n";
    outFile << "\t\t<thead>\n\t\t\t<tr>" << endl;
    for (std::string& t : QMLif::lastResult->title) {
        outFile << "\t\t\t\t<th>" << t.c_str() << endl;
    }
    outFile << "\t\t</thead>" << endl;
    outFile << "\t\t<tbody>" << endl;
    for (int i = counter * 50; i < counter * 50 + 50 && i < lastResult->data.size(); ++i) {
        outFile << "\t\t\t<tr>" << endl;
        for (std::string& t : lastResult->data[i]) {
            outFile << "\t\t\t\t<td>" << t.c_str() << endl;
        }
    }
    outFile << "\t\t</tbody>" << endl;
    outFile << "\t\t</table>" << endl;
    outFile << "</center>\t</body>\n</html>" << endl;
    return result;
}

void QMLif::getNetwork(const QString command) {
    counter = 0;
    QNetworkRequest request;
    request.setUrl(QUrl("http://128.199.74.228:5000/register"));
    QByteArray postData;
    postData.append(QString("name=ttbachyinsda&pass=123456789&method=execsql&sql=")+command);
    QNetworkReply *reply = manager.post(request,postData);
    
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinish(QNetworkReply*)));
}

void QMLif::replyFinish(QNetworkReply* reply) {
    json temp;
    QString Qtemp(reply->readAll());
//    cout << Qtemp.toStdString() << endl;
    temp = json::parse(Qtemp.toStdString());
    text.clear();
    
    if(temp["result"] != nullptr) {
        json result;
        string tempS = temp["result"];
        result = json::parse(tempS);
        cout << result.at(0).dump() << endl;
        QTextStream outFile(&text);
        outFile << "<!DOCTYPE html>\n<html>\n<style type=\"text/css\">\n" << testcss.c_str() << "</style>\n" << endl;
        outFile << "<body>\n<center>\t<table>\n\t\t<caption>Result</caption>\n";
//        outFile << "\t\t<thead>\n\t\t\t<tr>" << endl;
//        for (std::string& t : QMLif::lastResult->title) {
//            outFile << "\t\t\t\t<th>" << t.c_str() << endl;
//        }
//        outFile << "\t\t</thead>" << endl;
        outFile << "\t\t<tbody>" << endl;
        for (json r : result) {
            outFile << "\t\t\t<tr>" << endl;
            for (std::string t : r) {
                outFile << "\t\t\t\t<td>" << t.c_str() << endl;
            }
        }
        outFile << "\t\t</tbody>" << endl;
        outFile << "\t\t</table>" << endl;
        outFile << "</center>\t</body>\n</html>" << endl;
    }
    
    disconnect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinish(QNetworkReply*)));
    
    emit resultReady(text);
}

QMLif::QMLif() {
    text = "HaHa";
    i = 0;

    QNetworkRequest request;
    request.setUrl(QUrl("http://128.199.74.228:5000/register"));
    
    QByteArray postData;
    postData.append(QString("name=ttbachyinsda&pass=123456789&method=open"));
    QNetworkReply* reply = manager.post(request,postData);
    
    char temp[1024];
    ifstream inFile("test.css");
    cout<<"cdef"<<endl;
    testcss = "table {\
            border-collapse: collapse;\
            font-family: Futura, Arial, sans-serif;\
       }\
       \
       caption {\
            font-size: larger;\
            margin: 1em auto;\
       }\
       \
       th,td {\
            padding: .65em;\
       }\
       \
       th {\
           background: #555;\
           /* border: 1px solid #777; */\
           color: #fff;\
       }\
       \
       td {\
            /* border: 1px solid #777; */\
       }\
       \
       tbody tr:nth-child(odd) {\
            background: #ccc;\
       }\
       \
       th:first-child {\
            border-radius: 9px 0 0 0;\
       }\
       \
       th:last-child {\
            border-radius: 0 9px 0 0;\
       }\
       \
       tr:last-child td:first-child {\
            border-radius: 0 0 0 9px;\
       }\
       \
       tr:last-child td:last-child {\
            border-radius: 0 0 9px 0;\
       }";
//    while(!inFile.eof()) {
//        inFile.getline(temp, 1024);
//        testcss.append(string(temp));
//        testcss += "\n";
//    }
//    cout << testcss;
}
