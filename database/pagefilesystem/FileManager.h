#ifndef FILE_MANAGER
#define FILE_MANAGER
#include "MyBitMap.h"
#include "pagedef.h"
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
#ifndef PARA
#ifdef __linux
#define PARA O_RDWR
#elif __APPLE__
#define PARA O_RDWR
#else
#define PARA O_RDWR|O_BINARY
#endif
#endif
class FileManager {
private:
    //FileTable* ftable;
    int fd[MAX_FILE_NUM];
    MyBitMap* fm;
    MyBitMap* tm;
    int _createFile(const char* name)
    {
        FILE* f = fopen(name, "ab+");
        if (f == NULL) {
            cout << "fail" << endl;
            return -1;
        }
        fclose(f);
        return 0;
    }
    int _openFile(const char* name, int fileID)
    {
        int f = open(name, PARA);
        if (f == -1) {
            return -1;
        }
        fd[fileID] = f;
        return 0;
    }

public:
    /*
	 * FilManager构造函数
	 */
    FileManager()
    {
        fm = new MyBitMap(MAX_FILE_NUM, 1);
        tm = new MyBitMap(MAX_TYPE_NUM, 1);
    }
    /*
	 * @函数名writePage
	 * @参数fileID:文件id，用于区别已经打开的文件
	 * @参数pageID:文件的页号
	 * @参数buf:存储信息的缓存(4字节无符号整数数组)
	 * @参数off:偏移量
	 * 功能:将buf+off开始的2048个四字节整数(8kb信息)写入fileID和pageID指定的文件页中
	 * 返回:成功操作返回0
	 */
    int writePage(int fileID, int pageID, BufType buf, int off)
    {
        int f = fd[fileID];
        off_t offset = pageID;
        offset = (offset << PAGE_SIZE_IDX);
        off_t error = lseek(f, offset, SEEK_SET);
        if (error != offset) {
            return -1;
        }
        BufType b = buf + off;
        /*
        cout<<"Now begin "<<"testment"<<endl;
        for (int i=0;i<PAGE_INT_NUM;i++)
        {
            int k=b[i];
            cout<<"No."<<i<<" is: "<<k<<endl;
        }
        cout<<"Now end "<<"testment"<<endl;
        */
        error = write(f, (void*)b, PAGE_SIZE);
        return 0;
    }
    /*
	 * @函数名readPage
	 * @参数fileID:文件id，用于区别已经打开的文件
	 * @参数pageID:文件页号
	 * @参数buf:存储信息的缓存(4字节无符号整数数组)
	 * @参数off:偏移量
	 * 功能:将fileID和pageID指定的文件页中2048个四字节整数(8kb)读入到buf+off开始的内存中
	 * 返回:成功操作返回0
	 */
    int readPage(int fileID, int pageID, BufType buf, int off)
    {
        //int f = fd[fID[type]];
        int f = fd[fileID];
        off_t offset = pageID;
        offset = (offset << PAGE_SIZE_IDX);
        off_t error = lseek(f, offset, SEEK_SET);
        if (error != offset) {
            return -1;
        }
        BufType b = buf + off;
        error = read(f, (void*)b, PAGE_SIZE);
        return 0;
    }
    /*
	 * @函数名closeFile
	 * @参数fileID:用于区别已经打开的文件
	 * 功能:关闭文件
	 * 返回:操作成功，返回0
	 */
    int closeFile(int fileID)
    {
        fm->setBit(fileID, 1);
        int f = fd[fileID];
        close(f);
        return 0;
    }
    /*
	 * @函数名createFile
	 * @参数name:文件名
	 * 功能:新建name指定的文件名
	 * 返回:操作成功，返回true
	 */
    bool createFile(const char* name)
    {
        _createFile(name);
        return true;
    }
    /*
	 * @函数名openFile
	 * @参数name:文件名
	 * @参数fileID:函数返回时，如果成功打开文件，那么为该文件分配一个id，记录在fileID中
	 * 功能:打开文件
	 * 返回:如果成功打开，在fileID中存储为该文件分配的id，返回true，否则返回false
	 */
    bool openFile(const char* name, int& fileID)
    {
        fileID = fm->findLeftOne();
        fm->setBit(fileID, 0);
        int can = _openFile(name, fileID);
        if (can == 0)
            return true;
        else
            return false;
    }
    int newType()
    {
        int t = tm->findLeftOne();
        tm->setBit(t, 0);
        return t;
    }
    void closeType(int typeID)
    {
        tm->setBit(typeID, 1);
    }
    void shutdown()
    {
        delete tm;
        delete fm;
    }
    ~FileManager()
    {
        this->shutdown();
    }
};
#endif
