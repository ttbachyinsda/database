#ifndef DATABASE_H
#define DATABASE_H
#include "fixedsizetable.h"
#include "table.h"

class Database {
public:
    Database();
    Database(string filename);
    void setname(string name);
    void setfilename(string filename);
    string getname();
    string getfilename();
    bool Initialize();
    Table* getTable(int num);
    string getdatabasetype();
    Table* getTableByName(const std::string& name);
    void addTable(Table* now);
    void removeTable(int num);
    bool removeTableByName(const std::string& name);
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
