#ifndef TABLE_H
#define TABLE_H
#include "pagefilesystem/BufPageManager.h"
#include "recordhandler/record.h"
#include "typehandler/databasechar.h"
#include "typehandler/databaseint.h"
#include "typehandler/databasetype.h"
#include "DBIndex/db_index.h"
#include "managementhandler/uic.h"
#include <string>
#include <vector>
using namespace std;
#define MAX_NAME_SIZE 256
class Table {
public:
    Table();
    Table(string name, string filename);
    string getname();
    string getfilename();
    BufPageManager* getBPM();
    int getfileid();
    int getmajornum();
    void setmajornum(int nownum);
    db_index** getindexes();
    DataBaseType* getcolumn(int i);
    string getcolumnname(int i);
    DataBaseType** getcolumns();
    void setmultivalue(int i, bool istrue);
    bool getmultivalue(int i);
    int getcolumncount();
    bool setname(string name);
    void setfilename(string filename);
    bool checkInsert(vector<string> data);
    void readindex();
    void createemptyindex(int i);
    vector<string> checkOutput();
    virtual bool FastModify(int pagenum, int pageposition, Record* rec) = 0;
    virtual bool FastInsert(int& pagenum, int& pageposition, Record* rec) = 0;
    virtual bool FastAllInsert(int& pagenum, int& pageposition, Record* rec) = 0;
    virtual bool FastOutput(int pagenum, int pageposition, Record* rec) = 0;
    virtual void FastOutput(int pagenum, int pageposition, char* output, int& outputsize) = 0;
    virtual bool Initialize() = 0;
    virtual string gettabletype() = 0;
    bool havecreatetable = false;
    bool haveinitialize = false;
    virtual int getPageNum() = 0;
    virtual int getPageRowNum(int pagenum) = 0;
    virtual int getRowSize() = 0;
    virtual int getMaxRowNum() = 0;
    virtual bool Modify(int pagenum, int rownum) = 0;
    virtual bool DeleteAt(int pagenum, int rownum) = 0;
    virtual void createTable(vector<string> clname, vector<DataBaseType*> cltype) = 0;
    vector<string> gettype();
    virtual ~Table();

protected:
    void clearcolumn();
    void clearindex();
    void InsertindexAt(int num,char* insertdata,int datalen,int pagenum,int pageposition);
    void ModifyindexAt(int num,char* modifydata,int datalen,int prepagenum,int prepageposition,int newpagenum,int newpageposition);
    void DeleteindexAt(int num,char* deletedata,int datalen,int pagenum,int pageposition);
    string name;
    string filename;
    int fileid;
    int columncount;
    DataBaseType** column; //per size if 8
    string* columnname;
    int majornum;
    BufPageManager* BPM;
    FileManager* FM;
    db_index ** DBindex;
    bool* multivalue;
};

#endif // TABLE_H
