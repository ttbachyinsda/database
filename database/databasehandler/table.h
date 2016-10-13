#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <vector>
#include "typehandler/type.h"
#include "typehandler/databasechar.h"
#include "typehandler/databaseint.h"
#include "pagefilesystem/BufPageManager.h"
using namespace std;
#define MAX_NAME_SIZE 256
class Table
{
public:
    Table();
    Table(string name,string filename);
    string getname();
    string getfilename();
    type* getcolumn(int i);
    string getcolumnname(int i);
    bool setname(string name);
    void setfilename(string filename);
    bool checkInsert(vector<string> data);
    vector<string> checkOutput();
    virtual bool Insert()=0;
    virtual bool Initialize()=0;
    virtual bool DeleteAt(int pagenum,int rownum)=0;
    virtual bool FindAt(int pagenum,int rownum)=0;
    virtual void createTable(vector<string> clname,vector<string> cltype,vector<int> clsize)=0;
    vector<string> gettype();
    virtual ~Table();
protected:
    void clearcolumn();
    string name;
    string filename;
    int fileid;
    int columncount;
    vector<type*> column;
    vector<int> order;
    vector<string> columnname;
    BufPageManager* BPM;
    FileManager* FM;
};

#endif // TABLE_H
