#include "qmlif.h"
#include <fstream>
string QMLif::testcss;
SQLDriver QMLif::oldDriver;
QQuickItem *QMLif::dbList = 0;
using namespace std;

void WorkerThread::run() {
    QString result = "";
    driver->execute(command.toStdString());
    cout << command.toStdString() << endl;
    cout << driver->hasResult() << endl;
    QTextStream outFile(&result);
    outFile << "<!DOCTYPE html>\n<html>\n" << endl;
    if (driver->hasResult()) {
        outFile << "<body>\n<center>\t<table>\n\t\t<caption>Result</caption>\n";
        outFile << "\t\t<thead>\n\t\t\t<tr>" << endl;
        SQLResult* temp = driver->getResult();
        for (std::string& t : temp->title) {
            outFile << "\t\t\t\t<th>" << t.c_str() << endl;
        }
        outFile << "\t\t</thead>" << endl;
        outFile << "\t\t<tbody>" << endl;
        for (std::vector<std::string>& r : temp->data) {
            outFile << "\t\t\t<tr>" << endl;
            for (std::string& t : r) {
                outFile << "\t\t\t\t<td>" << t.c_str() << endl;
            }
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

QMLif::QMLif() {
    text = "HaHa";
    i = 0;

    char temp[1024];
    ifstream inFile("test.css");
    while(!inFile.eof()) {
        inFile.getline(temp, 1024);
        testcss.append(string(temp));
        testcss += "\n";
    }
//    cout << testcss;
}
