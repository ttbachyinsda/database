#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <vector>
#include "typehandler/databasetype.h"
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
    string getname();               //return the name of table
    string getfilename();           //return the filename of table
    DataBaseType* getcolumn(int i); //return the selected column of table
    string getcolumnname(int i);    //return the name of the selected column of table
    bool setname(string name);      //set the name of table
    void setfilename(string filename);  //set the filename of table
    bool checkInsert(vector<string> data);  //Check if data is correct, and cache it.
    vector<string> checkOutput();           //Check if data is correct, and output it.
    virtual bool Insert()=0;                //Insert the data in the cache
    virtual bool Initialize()=0;            //Initialize table
    bool havecreatetable=false;
    bool haveinitialize=false;
    virtual int getPageNum()=0;             //return the num of pages that table contains.
    virtual int getPageRowNum(int pagenum)=0; //return the number of rows in the selected page.
    virtual bool Modify(int pagenum,int rownum)=0; //modify a record
    virtual bool DeleteAt(int pagenum,int rownum)=0; //delete a record
    virtual bool FindAt(int pagenum,int rownum)=0;      //find a record and cache it
    virtual void createTable(vector<string> clname,vector<string> cltype,vector<int> clsize)=0; //create a table
    vector<string> gettype();   //return columns information
    virtual ~Table();           //destroy table, don't forget to execute it.
protected:
    void clearcolumn();
    string name;
    string filename;
    int fileid;
    int columncount;
    DataBaseType** column;           //per size if 8
    int * order;
    string * columnname;
    BufPageManager* BPM;
    FileManager* FM;
};

#endif // TABLE_H
