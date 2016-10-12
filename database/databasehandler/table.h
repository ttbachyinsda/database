#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <vector>
#include "typehandler/type.h"
#include "typehandler/databasechar.h"
#include "typehandler/databaseint.h"
#include "pagefilesystem/BufPageManager.h"
using namespace std;
class Table
{
public:
    Table();
    Table(string name,string filename);
    string getname();
    string getfilename();
    void setname(string name);
    void setfilename(string filename);
    virtual bool Initialize()=0;
    vector<string> gettype();
    virtual ~Table();
protected:
    string name;
    string filename;
    int fileid;
    vector<type*> column;
    vector<int> order;
    BufPageManager* BPM;
    FileManager* FM;
};

#endif // TABLE_H
