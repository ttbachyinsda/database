#ifndef DATABASE_H
#define DATABASE_H
#include "table.h"
#include "fixedsizetable.h"

class Database
{
public:
    Database();
    Database(string filename);
    void setname(string name);
    void setfilename(string filename);
    string getname();
    string getfilename();
    bool Initialize();
    Table * getTable(int num);
    void addTable(Table *now);
    void removeTable(int num);
    bool writeToFile();
    ~Database();
private:
    string name;
    string filename;
    vector<Table*> tablelist;
    int tablenum;
    FILE* f;
};

#endif // DATABASE_H
