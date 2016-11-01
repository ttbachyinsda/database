#include "database.h"

Database::Database()
{
    this->filename = "";
    this->tablenum = 0;
    this->f = NULL;
    this->tablelist.clear();
}
Database::Database(string filename)
{
    this->filename = filename;
    this->tablenum = 0;
    this->tablelist.clear();
    this->f = NULL;
}
Database::~Database()
{
    if (this->filename != "")
        writeToFile();
    for (int i = 0; i < this->tablenum; i++)
        delete this->tablelist[i];
    this->tablelist.clear();
    this->tablenum = 0;
    this->f = NULL;
}

void Database::setfilename(string filename) { this->filename = filename; }
void Database::setname(string name) { this->name = name; }
bool Database::writeToFile()
{
    this->f = fopen(this->filename.c_str(), "w");
    if (this->f == NULL)
        return false;
    fprintf(this->f, "%s\n", name.c_str());
    fprintf(this->f, "%d\n", tablenum);
    for (int i = 0; i < tablenum; i++) {
        fprintf(this->f, "%s\n", tablelist[i]->getfilename().c_str());
        fprintf(this->f, "%s\n", tablelist[i]->gettabletype().c_str());
    }
    fclose(this->f);
    return true;
}

bool Database::Initialize()
{
    for (int i = 0; i < this->tablenum; i++)
        if (tablelist[i] != NULL)
            delete tablelist[i];
    tablenum = 0;
    tablelist.clear();
    if (this->f != NULL)
        fclose(f);
    this->f = NULL;
    this->f = fopen(this->filename.c_str(), "r");
    if (this->f == NULL)
        return false;
    char* s = new char[256]; // Max name size is 256
    char* tp = new char[256];
    int can = fscanf(this->f, "%s", s);
    if (can == -1)
        return false;
    name = s;
    can = fscanf(this->f, "%d", &tablenum);
    if (can == -1)
        return false;
    for (int i = 0; i < tablenum; i++) {
        memset(s, 0, 256);
        can = fscanf(this->f, "%s", s);
        if (can == -1)
            return false;
        can = fscanf(this->f, "%s", tp);
        if (can == -1)
            return false;
        if (tp[0] == 'F') {
            Table* t = new FixedSizeTable();
            string temp = s;
            t->setfilename(temp);
            t->Initialize();
            tablelist.push_back(t);
        }
    }
    fclose(this->f);
    this->f = NULL;
    return true;
}
Table* Database::getTable(int num)
{
    if (num < tablenum)
        return tablelist[num];
    else
        return NULL;
}

Table *Database::getTableByName(const string &name)
{
    for (Table* tb : tablelist) {
        if (tb->getname() == name)
            return tb;
    }
    return NULL;
}

void Database::addTable(Table* now)
{
    tablenum++;
    tablelist.push_back(now);
}
void Database::removeTable(int num)
{
    Table* temp = tablelist.at(num);
    string tempfilename = temp->getfilename();
    if (temp != NULL)
        delete temp;
    remove(tempfilename.c_str());
    vector<Table*>::iterator k = tablelist.begin() + num;
    tablelist.erase(k);
    tablenum--;
}

bool Database::removeTableByName(const string &name)
{
    for (vector<Table*>::iterator it = tablelist.begin();
         it != tablelist.end(); ++ it) {
        if ((*it)->getname() == name) {
            Table* temp = *it;
            string tempFilename = temp->getfilename();
            delete temp;
            remove(tempFilename.c_str());
            tablelist.erase(it);
            -- tablenum;
            return true;
        }
    }
    return false;
}

string Database::getname() { return this->name; }
string Database::getfilename() { return this->filename; }

string Database::getdatabasetype()
{
    return "Database";
}
