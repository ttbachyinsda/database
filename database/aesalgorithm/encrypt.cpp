#include "encrypt.h"

void Encrypt::encryptafile(string filepath,string password)
{
    int can = access(filepath.c_str(), 0);
    if (can == -1) {
        cout<<"file not exist!"<<endl;
        return;
    }
    int fm = open(filepath.c_str(), PARA);
    if (fm == -1) {
        cout << "fail2" << endl;
        return;
    }

    int totalsize = get_file_size(filepath.c_str());

    BYTE* tempinput = (BYTE*)malloc(totalsize);
    BYTE* tempoutput = (BYTE*)malloc(totalsize);

    //initial password
    WORD key_schedule[60];
    string ivpassword = __iv__str;
    string md5pass = MD5(password).toStr();
    aes_key_setup((BYTE*)md5pass.data(), key_schedule, 256);

    read(fm,(void*)tempinput,totalsize);

    close(fm);

    fm = open(filepath.c_str(), PARA);
    if (fm == -1) {
        cout << "fail2" << endl;
        return;
    }

    aes_encrypt_ctr(tempinput, totalsize, tempoutput, key_schedule, 256, (BYTE*)ivpassword.data());

    write(fm,(void*)tempoutput,totalsize);

    close(fm);

    free(tempinput);
    free(tempoutput);

}

void Encrypt::decryptafile(string filepath,string password)
{
    int can = access(filepath.c_str(), 0);
    if (can == -1) {
        cout<<"file not exist!"<<endl;
        return;
    }
    int fm = open(filepath.c_str(), PARA);
    if (fm == -1) {
        cout << "fail2" << endl;
        return;
    }

    int totalsize = get_file_size(filepath.c_str());

    BYTE* tempinput = (BYTE*)malloc(totalsize);
    BYTE* tempoutput = (BYTE*)malloc(totalsize);

    //initial password
    WORD key_schedule[60];
    string ivpassword = __iv__str;
    string md5pass = MD5(password).toStr();
    aes_key_setup((BYTE*)md5pass.data(), key_schedule, 256);

    read(fm,(void*)tempinput,totalsize);

    close(fm);

    fm = open(filepath.c_str(), PARA);
    if (fm == -1) {
        cout << "fail2" << endl;
        return;
    }

    aes_decrypt_ctr(tempinput, totalsize, tempoutput, key_schedule, 256, (BYTE*)ivpassword.data());

    write(fm,(void*)tempoutput,totalsize);

    close(fm);

    free(tempinput);
    free(tempoutput);

}

unsigned long Encrypt::get_file_size(const char* path)
{
    unsigned long filesize = -1;
    struct stat statbuff;
    if (stat(path, &statbuff) < 0) {
        return filesize;
    } else {
        filesize = statbuff.st_size;
    }
    return filesize;
}
BYTE* Encrypt::trytodecrypt(string filepath,string password)
{
    int can = access(filepath.c_str(), 0);
    if (can == -1) {
        cout<<"file not exist!"<<endl;
        return NULL;
    }
    int fm = open(filepath.c_str(), PARA);
    if (fm == -1) {
        cout << "fail2" << endl;
        return NULL;
    }

    int totalsize = get_file_size(filepath.c_str());

    BYTE* tempinput = (BYTE*)malloc(totalsize);
    BYTE* tempoutput = (BYTE*)malloc(totalsize);

    //initial password
    WORD key_schedule[60];
    string ivpassword = __iv__str;
    string md5pass = MD5(password).toStr();
    aes_key_setup((BYTE*)md5pass.data(), key_schedule, 256);

    read(fm,(void*)tempinput,totalsize);

    close(fm);

    aes_decrypt_ctr(tempinput, totalsize, tempoutput, key_schedule, 256, (BYTE*)ivpassword.data());

    free(tempinput);

    return tempoutput;
}
void Encrypt::destroyafile(string filepath)
{
    int fm = open(filepath.c_str(), PARA);
    if (fm == -1) {
        return;
    }
    int totalsize = get_file_size(filepath.c_str());
    BYTE* empty = (BYTE*)malloc(totalsize);
    memset(empty,0,totalsize);
    write(fm,(void*)empty,totalsize);
    close(fm);
    free(empty);
}
string Encrypt::trytodecryptastr(string str,string password)
{
    BYTE* tempoutput = (BYTE*)malloc(str.length());

    //initial password
    WORD key_schedule[60];
    string ivpassword = __iv__str;
    string md5pass = MD5(password).toStr();
    aes_key_setup((BYTE*)md5pass.data(), key_schedule, 256);

    aes_decrypt_ctr((BYTE*)str.data(), str.length(), tempoutput, key_schedule, 256, (BYTE*)ivpassword.data());

    string temp((char*)tempoutput,str.length());
    free(tempoutput);

    return temp;
}
string Encrypt::trytoencryptastr(string str,string password)
{
    BYTE* tempoutput = (BYTE*)malloc(str.length());

    //initial password
    WORD key_schedule[60];
    string ivpassword = __iv__str;
    string md5pass = MD5(password).toStr();
    aes_key_setup((BYTE*)md5pass.data(), key_schedule, 256);

    aes_encrypt_ctr((BYTE*)str.data(), str.length(), tempoutput, key_schedule, 256, (BYTE*)ivpassword.data());

    string temp((char*)tempoutput,str.length());
    free(tempoutput);

    return temp;
}
