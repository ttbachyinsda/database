#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "../databasehandler/database.h"

class DatabaseManager {
public:
    DatabaseManager();
    DatabaseManager(string filename);
    void setname(string name);
    void setfilename(string filename);
    string getname();
    string getfilename();
    bool Initialize();
    Database* getDatabase(int num);
    Database* getDatabaseByName(const std::string&);
    void addDatabase(Database* now);
    void removeDatabase(int num);
    bool removeDatabaseByName(const std::string&);
    bool writeToFile();
    ~DatabaseManager();

private:
    string name;
    string filename;
    vector<Database*> databaselist;
    int databasenum;
    FILE* f;
};

#endif // DATABASEMANAGER_H
