#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "../databasehandler/database.h"
#include "../aesalgorithm/encrypt.h"
class DatabaseManager {
public:
    DatabaseManager();
    DatabaseManager(string filename);
    void setname(string name);
    void setfilename(string filename);
    string getname();
    string getfilename();
    int Initialize();
    Database* getDatabase(int num);
    Database* getDatabaseByName(const std::string&);
    void addDatabase(Database* now);
    void removeDatabase(int num);
    bool removeDatabaseByName(const std::string&);
    bool writeToFile();
    bool encrypt(string password);
    bool decrypt(string password);
    bool isencrypt();
    ~DatabaseManager();
    bool haveinitialized();
private:
    string keystr;
    string name;
    string filename;
    vector<Database*> databaselist;
    int databasenum;
    FILE* f;
    bool haveinitialize;
};

#endif // DATABASEMANAGER_H
