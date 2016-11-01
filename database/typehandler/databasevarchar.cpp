#include "databasevarchar.h"

DatabaseVarchar::DatabaseVarchar(int size)
{
    NullCondition();
    if (size > MAX_CHAR_SIZE)
        size = MAX_CHAR_SIZE;
    this->size = size;
    this->maxsize = size;
    data = (char*)malloc(maxsize + 1);
    memset(data, 0, maxsize + 1);
    this->Nullable = true;
    this->isNull = false;
}
DatabaseVarchar::DatabaseVarchar(int size, bool cannull)
{
    NullCondition();
    if (size > MAX_CHAR_SIZE)
        size = MAX_CHAR_SIZE;
    this->size = size;
    this->maxsize = size;
    data = (char*)malloc(maxsize + 1);
    memset(data, 0, maxsize + 1);
    this->Nullable = cannull;
    this->isNull = false;
}

/* Remember that if you input a string more than 255 characters or illegal, data will be
 * empty.
 * */
/*
DatabaseVarchar::DatabaseVarchar(string input,int maxsize)
{
    NullCondition();
    if (maxsize > MAX_CHAR_SIZE) maxsize = MAX_CHAR_SIZE;
    this->size = maxsize;
    this->maxsize = maxsize;
    bool can = checkRight(input);
    if (can) {
        this->size = input.length();
        data = (char*)malloc(this->maxsize + 1);
        memcpy(data, input.data(), this->size);
        data[this->size] = IS_NOT_NULL;
    } else {
        int size = input.length();
        if (size > maxsize)
            size = maxsize;
        this->size = size;
        data = (char*)malloc(this->maxsize + 1);
        memset(data, 0, this->maxsize + 1);
    }
    this->Nullable = true;
    this->isNull = false;
}
DatabaseVarchar::DatabaseVarchar(string input, bool cannull,int maxsize)
{
    NullCondition();
    if (maxsize > MAX_CHAR_SIZE) maxsize = MAX_CHAR_SIZE;
    this->size = maxsize;
    this->maxsize = maxsize;
    bool can = checkRight(input);
    if (can) {
        this->size = input.length();
        data = (char*)malloc(this->maxsize + 1);
        memcpy(data, input.data(), this->size);
        data[this->size] = IS_NOT_NULL;
    } else {
        int size = input.length();
        if (size > maxsize)
            size = maxsize;
        this->size = size;
        data = (char*)malloc(this->maxsize + 1);
        memset(data, 0, this->maxsize + 1);
    }
    this->Nullable = cannull;
    this->isNull = false;
}

DatabaseVarchar::DatabaseVarchar(char* input, int size,int maxsize)
{
    NullCondition();
    if (maxsize > MAX_CHAR_SIZE) maxsize = MAX_CHAR_SIZE;
    this->maxsize=maxsize;
    if (size <= maxsize) {
        this->size = size;
        data = (char*)malloc(this->maxsize + 1);
        memcpy(data, input, size);
        data[this->size] = IS_NOT_NULL;
    } else {
        this->size = maxsize;
        this->data = new char[this->maxsize + 1];
        memset(data, 0, this->maxsize + 1);
    }
    this->Nullable = true;
    this->isNull = false;
}
DatabaseVarchar::DatabaseVarchar(char* input, int size, bool cannull,int maxsize)
{
    NullCondition();
    if (maxsize > MAX_CHAR_SIZE) maxsize = MAX_CHAR_SIZE;
    this->maxsize=maxsize;
    if (size <= maxsize) {
        this->size = size;
        data = (char*)malloc(this->maxsize + 1);
        memcpy(data, input, size);
        data[this->size] = IS_NOT_NULL;
    } else {
        this->size = maxsize;
        this->data = new char[this->maxsize + 1];
        memset(data, 0, this->maxsize + 1);
    }
    this->Nullable = cannull;
    this->isNull = false;
}
*/
//Return length of type(Char)
int DatabaseVarchar::getSize()
{
    return this->size + 1;
}
int DatabaseVarchar::getRealSize()
{
    return this->size;
}
int DatabaseVarchar::getMaxSize()
{
    return this->maxsize+1;
}
/* Don't try to use them in a public method. Try to use checkRight or
 * checkRightAndChange instead.
 * */
void DatabaseVarchar::change(string input)
{
    isNull = false;
    int size = input.length();
    this->size=size;
    memset(data, 0, this->size);
    memcpy(data, input.data(), size);
    data[this->size] = IS_NOT_NULL;
}
void DatabaseVarchar::change(char* input, int size)
{
    isNull = false;
    this->size=size;
    memset(data, 0, this->size);
    memcpy(data, input, size);
    data[this->size] = IS_NOT_NULL;
}
void DatabaseVarchar::changetoNull()
{
    isNull = true;
    this->size=0;
    data[this->size] = IS_NULL;
}

/* Really commend to use these two methods
 * */
bool DatabaseVarchar::checkRight(string input)
{
    int lengthofinput = input.length();
    if (lengthofinput > this->maxsize)
        return false;
    return analysis(input);
}
bool DatabaseVarchar::checkRight(string input, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    int lengthofinput = input.length();
    if (lengthofinput > this->maxsize)
        return false;
    return analysis(input);
}
bool DatabaseVarchar::checkRightAndChange(string input)
{
    bool can = checkRight(input);
    if (can) {
        change(input);
        return true;
    }
    return false;
}
bool DatabaseVarchar::checkRightAndChange(string input, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull) {
        changetoNull();
        return true;
    }
    bool can = checkRight(input);
    if (can) {
        change(input);
        return true;
    }
    return false;
}
/* Don't Be careful to use these two methods. If you want to use that,
 * you can delete char*input,
 * because databasechar will copy the content.
 * */
bool DatabaseVarchar::checkRightc(char* input, int size)
{
    if (size > this->maxsize)
        return false;
    return analysisc(input, size);
}
bool DatabaseVarchar::checkRightc(char* input, int size, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    if (size > this->maxsize)
        return false;
    return analysisc(input, size);
}
bool DatabaseVarchar::checkRightAndChangec(char* input, int size)
{
    if (checkRightc(input, size)) {
        change(input, size);
        return true;
    }
    return false;
}
bool DatabaseVarchar::checkRightAndChangec(char* input, int size, bool inputisnull)
{
    if (checkRightc(input, size, inputisnull)) {
        change(input, size);
        return true;
    }
    return false;
}
/* Return the type and the maxlength of Type(char)
 * */
string DatabaseVarchar::getType()
{
    return "Type: VARC";
}
string DatabaseVarchar::output()
{
    if (isNull)
        return "NULL__DATA";
    string s(data, size);
    return s;
}

/* Don't delete that
 * */
DatabaseVarchar::~DatabaseVarchar()
{
}
bool DatabaseVarchar::read(char* input, int inputlen,int& position)
{
    this->size=inputlen-1;
    if (this->size>this->maxsize) this->size=this->maxsize;
    memcpy(data, input, this->size + 1);
    position += this->size + 1;
    if (data[this->size] == IS_NULL)
        this->isNull = true;
    else
        this->isNull = false;
    return true;
}
bool DatabaseVarchar::write(char* input, int& position)
{
    memcpy(input, data, this->size + 1);
    position += this->size + 1;
    return true;
}
bool DatabaseVarchar::analysis(string input)
{
    string analysistype(condition, 4);
    if (analysistype == "NULL")
        return true;
    if (analysistype == "FRTO") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input.data(), input.length());
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        int res2 = compare(temp, size + 1, par2, size + 1);
        free(temp);
        free(par1);
        free(par2);
        if (res1 >= 0 && res2 <= 0)
            return true;
        else
            return false;
    }
    if (analysistype == "frTO") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input.data(), input.length());
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        int res2 = compare(temp, size + 1, par2, size + 1);
        free(temp);
        free(par1);
        free(par2);
        if (res1 > 0 && res2 <= 0)
            return true;
        else
            return false;
    }
    if (analysistype == "FRto") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input.data(), input.length());
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        int res2 = compare(temp, size + 1, par2, size + 1);
        free(temp);
        free(par1);
        free(par2);
        if (res1 >= 0 && res2 < 0)
            return true;
        else
            return false;
    }
    if (analysistype == "frto") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input.data(), input.length());
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        int res2 = compare(temp, size + 1, par2, size + 1);
        free(temp);
        free(par1);
        free(par2);
        if (res1 > 0 && res2 < 0)
            return true;
        else
            return false;
    }
    if (analysistype == "NTEQ") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input.data(), input.length());
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        free(temp);
        free(par1);
        if (res1 == 0)
            return true;
        else
            return false;
    }
    if (analysistype == "CHOI") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input.data(), input.length());
        string paras(condition + 4, 4);
        int paranum = stringtoint(paras);
        char* par = (char*)malloc(size + 1);
        for (int i = 0; i < paranum; i++) {
            memcpy(par, condition + 8 + i * (size + 1), size + 1);
            int res = compare(temp, size + 1, par, size + 1);
            if (res == 0) {
                free(par);
                free(temp);
                return true;
            }
        }
        free(par);
        free(temp);
        return false;
    }
    cout << "ERROR: No condition will be NUll" << endl;
    NullCondition();
    return true;
}
bool DatabaseVarchar::analysisc(char* input, int inputsize)
{
    string analysistype(condition, 4);
    if (analysistype == "NULL")
        return true;
    if (analysistype == "FRTO") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input, inputsize);
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        int res2 = compare(temp, size + 1, par2, size + 1);
        free(temp);
        free(par1);
        free(par2);
        if (res1 >= 0 && res2 <= 0)
            return true;
        else
            return false;
    }
    if (analysistype == "frTO") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input, inputsize);
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        int res2 = compare(temp, size + 1, par2, size + 1);
        free(temp);
        free(par1);
        free(par2);
        if (res1 > 0 && res2 <= 0)
            return true;
        else
            return false;
    }
    if (analysistype == "FRto") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input, inputsize);
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        int res2 = compare(temp, size + 1, par2, size + 1);
        free(temp);
        free(par1);
        free(par2);
        if (res1 >= 0 && res2 < 0)
            return true;
        else
            return false;
    }
    if (analysistype == "frto") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input, inputsize);
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        int res2 = compare(temp, size + 1, par2, size + 1);
        free(temp);
        free(par1);
        free(par2);
        if (res1 > 0 && res2 < 0)
            return true;
        else
            return false;
    }
    if (analysistype == "NTEQ") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input, inputsize);
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        int res1 = compare(temp, size + 1, par1, size + 1);
        free(temp);
        free(par1);
        if (res1 == 0)
            return true;
        else
            return false;
    }
    if (analysistype == "CHOI") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp, input, inputsize);
        string paras(condition + 4, 4);
        int paranum = stringtoint(paras);
        char* par = (char*)malloc(size + 1);
        for (int i = 0; i < paranum; i++) {
            memcpy(par, condition + 8 + i * (size + 1), size + 1);
            int res = compare(temp, size + 1, par, size + 1);
            if (res == 0) {
                free(par);
                free(temp);
                return true;
            }
        }
        free(par);
        free(temp);
        return false;
    }
    cout << "ERROR: No condition will be NUll" << endl;
    NullCondition();
    return true;
}
