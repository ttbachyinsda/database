#include "testaes.h"

testaes::testaes()
{

}
void testaes::begintest()
{
    AESWORD key_schedule[60];
        BYTE enc_buf[128];
        string plainstring = "I am a student.wefewfwefwfew?";
        string password = "3123456";
        string ivpassword = "Iamattbachyinsda";
        string md5pass = MD5(password).toStr();
        cout<<md5pass.length()<<endl;

        cout<<plainstring.length()<<endl;
        BYTE* plaintext = (BYTE*)malloc(plainstring.length());
        BYTE* rectext = (BYTE*)malloc(plainstring.length());
        memcpy(plaintext,plainstring.data(),plainstring.length());

        aes_key_setup((BYTE*)md5pass.data(), key_schedule, 256);


        aes_encrypt_ctr((BYTE*)plainstring.c_str(), plainstring.length(), enc_buf, key_schedule, 256, (BYTE*)ivpassword.data());
        aes_decrypt_ctr(enc_buf,plainstring.length(),rectext,key_schedule,256,(BYTE*)ivpassword.data());
        string t((char*)rectext,plainstring.length());
        cout<<t<<endl;
}
void testaes::encryptafile(string filepath,string password)
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
    AESWORD key_schedule[60];
    string ivpassword = "Iamattbachyinsda";
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

}

void testaes::decryptafile(string filepath,string password)
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
    AESWORD key_schedule[60];
    string ivpassword = "Iamattbachyinsda";
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

}

unsigned long testaes::get_file_size(const char* path)
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
