#include "bulbfile.h"

void BulbFile::setfilename(string filename, bool reconstruct)
{
    if (fm != -1) close(fm);
    if (reconstruct == true)
    {
        remove(filename.c_str());
    }
    FILE* f = fopen(filename.c_str(), "ab+");
    if (f == NULL) {
        cout << "fail" << endl;
        return;
    }
    fclose(f);

    fm = open(filename.c_str(), PARA);
    if (fm == -1) {
        cout<< "fail2"<< endl;
        return;
    }

    totalsize = get_file_size(filename.c_str());
}
unsigned long BulbFile::get_file_size(const char *path)
{
    unsigned long filesize = -1;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0){
        return filesize;
    }else{
        filesize = statbuff.st_size;
    }
    return filesize;
}
int BulbFile::put(char *input, int size)
{
    assert(fm != -1);
    int f = fm;
    off_t oft = lseek(f, totalsize, 0);
    oft = write(f, (void*)input, size);
    int nowof = totalsize;
    totalsize += size;
    return nowof;
}
int BulbFile::put(const char *input, int size)
{
    assert(fm != -1);
    int f = fm;
    off_t oft = lseek(f, totalsize, 0);
    oft = write(f, (void*)input, size);
    int nowof = totalsize;
    totalsize += size;
    return nowof;
}
string BulbFile::get(int offset,int size)
{
    assert(fm != -1);
    int f = fm;
    off_t oft = lseek(f, offset, 0);
    char temp[size];
    oft = read(f,(void*)temp,size);
    string t(temp,size);
    return t;
}
char* BulbFile::getc(int offset, int size)
{
    assert(fm != -1);
    int f = fm;
    off_t oft = lseek(f, offset, 0);
    char* temp = (char*)malloc(size);
    oft = read(f,(void*)temp,size);
    return temp;
}
