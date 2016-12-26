#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{
    this->filename = "";
    this->databasenum = 0;
    this->f = NULL;
    this->databaselist.clear();
    this->keystr = __iv__str;
}
DatabaseManager::DatabaseManager(string filename)
{
    this->filename = filename;
    this->databasenum = 0;
    this->databaselist.clear();
    this->f = NULL;
    this->keystr = __iv__str;
}
DatabaseManager::~DatabaseManager()
{
    if (this->filename != "" && this->keystr == __iv__str)
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
    this->f = fopen(this->filename.c_str(), "wb");
    if (this->f == NULL)
        return false;
    fwrite(keystr.data(),1,keystr.length(),this->f);
    fprintf(this->f, "%s\n", name.c_str());
    fprintf(this->f, "%d\n", databasenum);
    for (int i = 0; i < databasenum; i++) {
        fprintf(this->f, "%s\n", databaselist[i]->getfilename().c_str());
        fprintf(this->f, "%s\n", databaselist[i]->getdatabasetype().c_str());
    }
    fclose(this->f);
    this->f = NULL;
    return true;
}

int DatabaseManager::Initialize()
{
    for (int i = 0; i < this->databasenum; i++)
        if (databaselist[i] != NULL)
            delete databaselist[i];
    databasenum = 0;
    databaselist.clear();
    if (this->f != NULL)
        fclose(f);
    this->f = NULL;
    int hasfile = access(this->filename.c_str(), 0);
    if (hasfile == -1) {
        writeToFile();
    }
    this->f = fopen(this->filename.c_str(), "rb");
    if (this->f == NULL)
    {
        cout<<"ERROR:: unknown error"<<endl;
        return 0;
    }
    char s[256],tp[256]; //Max name size is 256

    this->keystr = __iv__str;
    char keystrtemp[100];
    fread(keystrtemp,1,this->keystr.length(),this->f);
    string tempkeystr(keystrtemp,this->keystr.length());
    this->keystr = tempkeystr;

    if (this->keystr != __iv__str)
    {
        //databasemanager is encrypted
        fclose(this->f);
        this->f = NULL;
        return -1;
    }

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
            t->Initialize();
            databaselist.push_back(t);
        }
    }
    fclose(this->f);
    this->f = NULL;

    //succeed without password
    return 1;
}
Database* DatabaseManager::getDatabase(int num)
{
    if (num < databasenum)
        return databaselist[num];
    else
        return NULL;
}

Database* DatabaseManager::getDatabaseByName(const string& name)
{
    for (Database* db : databaselist) {
        if (db->getname() == name)
            return db;
    }
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

bool DatabaseManager::removeDatabaseByName(const string& name)
{
    for (vector<Database*>::iterator it = databaselist.begin();
         it != databaselist.end(); ++it) {
        if ((*it)->getname() == name) {
            Database* temp = *it;
            string tempFilename = temp->getfilename();
            delete temp;
            remove(tempFilename.c_str());
            databaselist.erase(it);
            --databasenum;
            return true;
        }
    }
    return false;
}

string DatabaseManager::getname()
{
    return this->name;
}
string DatabaseManager::getfilename()
{
    return this->filename;
}

bool DatabaseManager::encrypt(string password)
{
    if (this->keystr != __iv__str)
    {
        //is encrypted now
        return false;
    }
    this->keystr = Encrypt::trytoencryptastr(this->keystr,password);

    writeToFile();
    for (int i = 0; i < this->databasenum; i++)
        if (databaselist[i] != NULL)
            delete databaselist[i];
    databasenum = 0;
    this->databaselist.clear();

    this->f = fopen(this->filename.c_str(), "rb");
    char s[256],tp[256]; //Max name size is 256
    char s1[256],tp1[256];
    char keystrtemp[100];
    fread(keystrtemp,1,this->keystr.length(),this->f);
    int tempdatabasenum;
    fscanf(this->f, "%s", s);
    fscanf(this->f, "%d", &tempdatabasenum);
    for (int i = 0; i < tempdatabasenum; i++) {
        memset(s, 0, 256);
        fscanf(this->f, "%s", s);
        fscanf(this->f, "%s", tp);
        if (tp[0] == 'D') {
            FILE *g;
            g = fopen(s,"r");
            int can = fscanf(g, "%s", s1);

            int tablenum;
            can = fscanf(g, "%d", &tablenum);

            for (int i = 0; i < tablenum; i++) {
                memset(s1, 0, 256);
                can = fscanf(g, "%s", s1);
                can = fscanf(g, "%s", tp1);

                string tablepath = s1;
                Encrypt::encryptafile(tablepath,password);
            }
            fclose(g);
        }
    }
    fclose(this->f);
    this->f = NULL;
    return true;
}

bool DatabaseManager::decrypt(string password)
{
    if (this->keystr == __iv__str)
    {
        //is not encrypted now
        return false;
    }
    auto temp = Encrypt::trytodecryptastr(this->keystr,password);
    if (temp != __iv__str)
    {
        //password wrong
        return false;
    }

    this->keystr = temp;

    this->f = fopen(this->filename.c_str(), "rb");
    char s[256],tp[256]; //Max name size is 256
    char s1[256],tp1[256];
    char keystrtemp[100];
    fread(keystrtemp,1,this->keystr.length(),this->f);
    int tempdatabasenum;
    fscanf(this->f, "%s", s);
    fscanf(this->f, "%d", &tempdatabasenum);
    for (int i = 0; i < tempdatabasenum; i++) {
        memset(s, 0, 256);
        fscanf(this->f, "%s", s);
        fscanf(this->f, "%s", tp);
        if (tp[0] == 'D') {
            FILE *g;
            g = fopen(s,"r");
            int can = fscanf(g, "%s", s1);

            int tablenum;
            can = fscanf(g, "%d", &tablenum);

            for (int i = 0; i < tablenum; i++) {
                memset(s1, 0, 256);
                can = fscanf(g, "%s", s1);
                can = fscanf(g, "%s", tp1);

                string tablepath = s1;
                Encrypt::decryptafile(tablepath,password);
            }
            fclose(g);
        }
    }
    fclose(this->f);
    this->f = NULL;

    unsigned int size = Encrypt::get_file_size(this->filename.c_str());
    char* tempmanager = (char*)malloc(size);
    this->f = fopen(this->filename.c_str(), "rb");
    fread(tempmanager,1,size,this->f);
    memcpy(tempmanager,this->keystr.data(),this->keystr.length());
    fclose(this->f);

    this->f = fopen(this->filename.c_str(), "wb");
    fwrite(tempmanager,1,size,this->f);
    fclose(this->f);
    this->f = NULL;

    free(tempmanager);

    return true;
}
bool DatabaseManager::isencrypt()
{
    if (this->keystr == __iv__str) return false;
    else return true;
}
