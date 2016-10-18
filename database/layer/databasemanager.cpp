#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{
    this->filename = "";
    this->databasenum = 0;
    this->f = NULL;
    this->databaselist.clear();
}
DatabaseManager::DatabaseManager(string filename)
{
    this->filename = filename;
    this->databasenum = 0;
    this->databaselist.clear();
    this->f = NULL;
    writeToFile();
}
DatabaseManager::~DatabaseManager()
{
    if (this->filename != "")
        writeToFile();
    for (int i = 0; i < this->databasenum; i++)
        delete this->databaselist[i];
    this->databaselist.clear();
    this->databasenum = 0;
    this->f = NULL;
}

void DatabaseManager::setfilename(string filename)
{
    this->filename = filename;
}
void DatabaseManager::setname(string name)
{
    this->name = name;
}
bool DatabaseManager::writeToFile()
{
    this->f = fopen(this->filename.c_str(), "w");
    if (this->f == NULL)
        return false;
    fprintf(this->f, "%s\n", name.c_str());
    fprintf(this->f, "%d\n", databasenum);
    for (int i = 0; i < databasenum; i++) {
        fprintf(this->f, "%s\n", databaselist[i]->getfilename().c_str());
    }
    fclose(this->f);
    return true;
}

bool DatabaseManager::Initialize()
{
    for (int i = 0; i < this->databasenum; i++)
        if (databaselist[i] != NULL)
            delete databaselist[i];
    databasenum = 0;
    databaselist.clear();
    if (this->f != NULL)
        fclose(f);
    this->f = NULL;
    this->f = fopen(this->filename.c_str(), "r");
    if (this->f == NULL)
        return false;
    char* s = new char[256]; //Max name size is 256
    char* tp = new char[256];
    fscanf(this->f, "%s", s);
    name = s;
    fscanf(this->f, "%d", &databasenum);
    for (int i = 0; i < databasenum; i++) {
        memset(s, 0, 256);
        fscanf(this->f, "%s", s);
        fscanf(this->f, "%s", tp);
        if (tp[0] == 'D') {
            Database* t = new Database();
            string temp = s;
            t->setfilename(temp);
            databaselist.push_back(t);
        }
    }
    fclose(this->f);
    this->f = NULL;
    return true;
}
Database* DatabaseManager::getDatabase(int num)
{
    if (num < databasenum)
        return databaselist[num];
    else
        return NULL;
}
void DatabaseManager::addDatabase(Database* now)
{
    databasenum++;
    databaselist.push_back(now);
}
void DatabaseManager::removeDatabase(int num)
{
    Database* temp = databaselist.at(num);
    string tempfilename = temp->getfilename();
    if (temp != NULL)
        delete temp;
    remove(tempfilename.c_str());
    vector<Database*>::iterator k = databaselist.begin() + num;
    databaselist.erase(k);
    databasenum--;
}
string DatabaseManager::getname()
{
    return this->name;
}
string DatabaseManager::getfilename()
{
    return this->filename;
}
