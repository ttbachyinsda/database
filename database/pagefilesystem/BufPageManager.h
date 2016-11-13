#ifndef BUF_PAGE_MANAGER
#define BUF_PAGE_MANAGER
/*
 * BufPageManager
 * ���������������������������������
 */
#include "FileManager.h"
#include "FindReplace.h"
#include "MyHashMap.h"
#include <cstring>
class BufPageManager {
public:
    int last;
    FileManager* fileManager;
    MyHashMap* hash;
    FindReplace* replace;
    //MyLinkList* bpl;
    bool* dirty;
    /*
     * ������������������
     */
    BufType* addr;
    BufType allocMem()
    {
        char* s = new char[PAGE_SIZE];
        memset(s,0,PAGE_SIZE);
        return s;
    }
    BufType fetchPage(int typeID, int pageID, int& index)
    {
        BufType b;
        index = replace->find();
        b = addr[index];
        if (b == NULL) {
            b = allocMem();
            addr[index] = b;
        } else {
            if (dirty[index]) {
                int k1, k2;
                hash->getKeys(index, k1, k2);
                fileManager->writePage(k1, k2, b, 0);
                dirty[index] = false;
            }
            memset(b,0,PAGE_SIZE);
        }
        hash->replace(index, typeID, pageID);
        return b;
    }

public:
    /*
     * @���������allocPage
     * @������fileID:������id������������������������������������������id���������������������������������������
     * @������pageID:������������������������fileID���������������������������������������
     * @������index:������������������������������������������������������������
     * @������ifRead:������������������������������������������������
     * ������:������������������������
     * ������:������������������������������������������������������������
     *           ������������������������������������������������������������index���
     *           ���������ifRead���������true���������������������������������������������������������������
     * ������:���������������allocPage������������������������������(fileID,pageID)���������������������������������������
     *           ���������������������������������������������������������������������hash������������������������������������������������������������
     */
    BufType allocPage(int fileID, int pageID, int& index, bool ifRead = false)
    {
        BufType b = fetchPage(fileID, pageID, index);
        if (ifRead) {
            fileManager->readPage(fileID, pageID, b, 0);
        }
        return b;
    }
    /*
     * @���������getPage
     * @������fileID:������id
     * @������pageID:������������
     * @������index:������������������������������������������������������������
     * ������:������������������������
     * ������:���������������������������������������������������������������������
     *           ���������������(fileID,pageID)������
     *           ������������������������������������������������������������index���
     *           ������������hash������������(fileID,pageID)������������������������
     *           ������������������������������������������������������
     *           ������������������������������������������������������������������
     */
    BufType getPage(int fileID, int pageID, int& index)
    {
        index = hash->findIndex(fileID, pageID);
        if (index != -1) {
            access(index);
            return addr[index];
        } else {
            BufType b = fetchPage(fileID, pageID, index);
            fileManager->readPage(fileID, pageID, b, 0);
            return b;
        }
    }
    /*
     * @���������access
     * @������index:���������������������������������������������������������������
     * ������:������index���������������������������������������������������������������
     */
    void access(int index)
    {
        if (index == last) {
            return;
        }
        replace->access(index);
        last = index;
    }
    /*
     * @���������markDirty
     * @������index:���������������������������������������������������������������
     * ������:������index������������������������������������������������������������������������������������������������
     *           ������������������������
     */
    void markDirty(int index)
    {
        dirty[index] = true;
        access(index);
    }
    /*
     * @���������release
     * @������index:���������������������������������������������������������������
     * ������:���index������������������������������������������������������������������������������������������������������
     */
    void release(int index)
    {
        dirty[index] = false;
        replace->free(index);
        hash->remove(index);
    }
    /*
     * @���������writeBack
     * @������index:���������������������������������������������������������������
     * ������:���index���������������������������������������������������������������������������������������������������������������������������������������������������������
     */
    void writeBack(int index)
    {
        if (dirty[index]) {
            int f, p;
            hash->getKeys(index, f, p);
            fileManager->writePage(f, p, addr[index], 0);
            dirty[index] = false;
        }
        replace->free(index);
        hash->remove(index);
    }
    /*
     * @���������close
     * ������:���������������������������������������������������������������������������������������������������������������������������
     */
    void close()
    {
        for (int i = 0; i < CAP; ++i) {
            writeBack(i);
        }
    }
    /*
     * @���������getKeyint h
     * @������index:���������������������������������������������������������������
     * @������fileID:������������������������������������������������������������������
     * @������pageID:���������������������������������������������������������������������
     */
    void getKey(int index, int& fileID, int& pageID)
    {
        hash->getKeys(index, fileID, pageID);
    }
    /*
     * ������������
     * @������fm:���������������������������������������������������������������������������������
     */
    BufPageManager(FileManager* fm)
    {
        int c = CAP;
        int m = MOD;
        last = -1;
        fileManager = fm;
        //bpl = new MyLinkList(CAP, MAX_FILE_NUM);
        dirty = new bool[CAP];
        addr = new BufType[CAP];
        hash = new MyHashMap(c, m);
        replace = new FindReplace(c);
        for (int i = 0; i < CAP; ++i) {
            dirty[i] = false;
            addr[i] = NULL;
        }
    }
    ~BufPageManager()
    {
        if (dirty!=NULL) delete[] dirty;
        for (int i = 0; i < CAP; ++i) {
            if (addr[i]!=NULL) delete[] addr[i];
        }
        delete[] addr;
        if (hash!=NULL) delete hash;
        if (replace!=NULL) delete replace;
    }
};
#endif
