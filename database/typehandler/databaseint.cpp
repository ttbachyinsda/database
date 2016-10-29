#include "databaseint.h"
/*We should know that the max size of type(Int) is 255, if you set the size larger than 255
 * the size will force to be 255, whatever your input is.
 * */
DatabaseInt::DatabaseInt(int size)
{
    NullCondition();
    if (size > MAX_INT_SIZE)
        size = MAX_INT_SIZE;
    this->size = size;
    data = (char*)malloc(size + 1);
    memset(data, 0, size + 1);
    this->Nullable = true;
    this->isNull = false;
}
DatabaseInt::DatabaseInt(int size, bool cannull)
{
    NullCondition();
    if (size > MAX_INT_SIZE)
        size = MAX_INT_SIZE;
    this->size = size;
    data = (char*)malloc(size + 1);
    memset(data, 0, size + 1);
    this->Nullable = cannull;
    this->isNull = false;
}
/* Remember that if you input a string more than 255 characters or illegal, data will be
 * empty.
 * */
DatabaseInt::DatabaseInt(string input)
{
    NullCondition();
    this->size = MAX_INT_SIZE;
    bool can = checkRight(input);
    if (can) {
        this->size = input.length();
        data = (char*)malloc(this->size + 1);
        memcpy(data, input.data(), this->size);
        data[size] = IS_NOT_NULL;
    } else {
        int size = input.length();
        if (size > MAX_INT_SIZE)
            size = MAX_INT_SIZE;
        this->size = size;
        data = (char*)malloc(size + 1);
        memset(data, 0, size + 1);
    }
    this->Nullable = true;
    this->isNull = false;
}
DatabaseInt::DatabaseInt(string input, bool cannull)
{
    NullCondition();
    this->size = MAX_INT_SIZE;
    bool can = checkRight(input);
    if (can) {
        this->size = input.length();
        data = (char*)malloc(this->size + 1);
        memcpy(data, input.data(), this->size);
        data[size] = IS_NOT_NULL;
    } else {
        int size = input.length();
        if (size > MAX_INT_SIZE)
            size = MAX_INT_SIZE;
        this->size = size;
        data = (char*)malloc(size + 1);
        memset(data, 0, size + 1);
    }
    this->Nullable = cannull;
    this->isNull = false;
}
DatabaseInt::DatabaseInt(char* input, int size)
{
    NullCondition();
    this->size = MAX_INT_SIZE;
    bool can = checkRight(input, size);
    if (can) {
        this->size = size;
        data = (char*)malloc(size + 1);
        memcpy(data, input, size);
        data[size] = IS_NOT_NULL;
    } else {
        if (size > MAX_INT_SIZE)
            size = MAX_INT_SIZE;
        this->size = size;
        this->data = (char*)malloc(size + 1);
        memset(data, 0, size + 1);
    }
    this->Nullable = true;
    this->isNull = false;
}
DatabaseInt::DatabaseInt(char* input, int size, bool cannull)
{
    NullCondition();
    this->size = MAX_INT_SIZE;
    bool can = checkRight(input, size);
    if (can) {
        this->size = size;
        data = (char*)malloc(size + 1);
        memcpy(data, input, size);
        data[size] = IS_NOT_NULL;
    } else {
        if (size > MAX_INT_SIZE)
            size = MAX_INT_SIZE;
        this->size = size;
        this->data = (char*)malloc(size + 1);
        memset(data, 0, size + 1);
    }
    this->Nullable = cannull;
    this->isNull = false;
}
//Return length of type(Int)
int DatabaseInt::getSize()
{
    return this->size + 1;
}
int DatabaseInt::getRealSize()
{
    return this->size;
}
int DatabaseInt::getMaxSize()
{
    return this->size + 1;
}
/* Don't try to use it in a public method. Try to use checkRight or
 * checkRightAndChange instead.
 * */
void DatabaseInt::change(string input)
{
    isNull = false;
    int size = input.length();
    memset(data, 0, this->size);
    memcpy(data + (this->size - size), input.data(), size);
    data[this->size] = IS_NOT_NULL;
    this->isNull = false;
}
void DatabaseInt::change(char* input, int size)
{
    isNull = false;
    memset(data, 0, this->size);
    memcpy(data + (this->size - size), input, size);
    data[this->size] = IS_NOT_NULL;
    this->isNull = false;
}
void DatabaseInt::changetoNull()
{
    isNull = true;
    data[this->size] = IS_NULL;
}

/* Really commend to use these two methods
 * */
bool DatabaseInt::checkRight(string input)
{
    int lengthofinput = input.length();
    if (lengthofinput > this->size)
        return false;
    for (int i = 0; i < lengthofinput; i++)
        if (input[i] < '0' || input[i] > '9')
            return false;
    return analysis(input);
}
bool DatabaseInt::checkRight(string input, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    int lengthofinput = input.length();
    if (lengthofinput > this->size)
        return false;
    for (int i = 0; i < lengthofinput; i++)
        if (input[i] < '0' || input[i] > '9')
            return false;
    return analysis(input);
}
bool DatabaseInt::checkRightAndChange(string input)
{
    bool can = checkRight(input);
    if (can) {
        change(input);
        return true;
    }
    if (isNull)
        return "NULL__DATA";
    return false;
}
bool DatabaseInt::checkRightAndChange(string input, bool inputisnull)
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
    if (isNull)
        return "NULL__DATA";
    return false;
}
/* Be careful to use these two methods. If you want to use that, don't delete char*input,
 * because databasechar will not copy the content.
 * */
bool DatabaseInt::checkRightc(char* input, int size)
{
    if (size > this->size)
        return false;
    for (int i = 0; i < size; i++)
        if (*(input + i) < '0' || *(input + i) > '9')
            if (*(input + i) != 0)
                return false;
    return analysisc(input, size);
}
bool DatabaseInt::checkRightc(char* input, int size, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    if (size > this->size)
        return false;
    for (int i = 0; i < size; i++)
        if (*(input + i) < '0' || *(input + i) > '9')
            if (*(input + i) != 0)
                return false;
    return analysisc(input, size);
}
bool DatabaseInt::checkRightAndChangec(char* input, int size)
{
    bool can = checkRightc(input, size);
    if (can) {
        change(input, size);
        return true;
    }
    return false;
}
bool DatabaseInt::checkRightAndChangec(char* input, int size, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull) {
        changetoNull();
        return true;
    }
    bool can = checkRightc(input, size);
    if (can) {
        change(input, size);
        return true;
    }
    return false;
}
/* Return the type and the maxlength of Type(char)
 * */
string DatabaseInt::getType()
{
    return "Type: INTE";
}
string DatabaseInt::output()
{
    if (isNull)
        return "NULL__DATA";
    char* tmp = new char[size];
    memcpy(tmp, data, size);
    for (int i = 0; i < size; i++)
        if (*(tmp + i) == 0 || *(tmp + i) == 32)
            *(tmp + i) = '0';
    string s(tmp, size);
    return s;
}

/* Don't delete that
 * */
DatabaseInt::~DatabaseInt()
{
}
bool DatabaseInt::read(char* input, int inputlen,int& position)
{
    memcpy(data, input, this->size + 1);
    position += this->size + 1;
    if (data[this->size] == IS_NULL)
        this->isNull = true;
    else
        this->isNull = false;
    return true;
}
bool DatabaseInt::write(char* input, int& position)
{
    memcpy(input, data, this->size + 1);
    position += this->size + 1;
    return true;
}
bool DatabaseInt::analysis(string input)
{
    string analysistype(condition, 4);
    if (analysistype == "NULL")
        return true;
    if (analysistype == "FRTO") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp + (size - input.length()), input.data(), input.length());
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par2 + i) == 0 || *(par2 + i) == 32)
                *(par2 + i) = '0';
        int res1 = compare(temp, size , par1, size );
        int res2 = compare(temp, size , par2, size );
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
        memcpy(temp + (size - input.length()), input.data(), input.length());
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par2 + i) == 0 || *(par2 + i) == 32)
                *(par2 + i) = '0';
        int res1 = compare(temp, size , par1, size );
        int res2 = compare(temp, size , par2, size );
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
        memcpy(temp + (size - input.length()), input.data(), input.length());
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par2 + i) == 0 || *(par2 + i) == 32)
                *(par2 + i) = '0';
        int res1 = compare(temp, size , par1, size );
        int res2 = compare(temp, size , par2, size );
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
        memcpy(temp + (size - input.length()), input.data(), input.length());
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par2 + i) == 0 || *(par2 + i) == 32)
                *(par2 + i) = '0';
        int res1 = compare(temp, size , par1, size );
        int res2 = compare(temp, size , par2, size );
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
        memcpy(temp + (size - input.length()), input.data(), input.length());
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
        int res1 = compare(temp, size , par1, size );
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
        memcpy(temp + (size - input.length()), input.data(), input.length());
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        int paranum = chartoint(condition + 4);
        char* par = (char*)malloc(size + 1);
        for (int i = 0; i < paranum; i++) {
            memcpy(par, condition + 8 + i * (size + 1), size + 1);
            for (int i = 0; i < size; i++)
                if (*(par + i) == 0 || *(par + i) == 32)
                    *(par + i) = '0';
            int res = compare(temp, size , par, size );
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
bool DatabaseInt::analysisc(char* input, int inputsize)
{
    string analysistype(condition, 4);
    if (analysistype == "NULL")
        return true;
    if (analysistype == "FRTO") {
        char* temp = (char*)malloc(size + 1);
        memset(temp, 0, size + 1);
        memcpy(temp + (size - inputsize), input, inputsize);
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par2 + i) == 0 || *(par2 + i) == 32)
                *(par2 + i) = '0';
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
        memcpy(temp + (size - inputsize), input, inputsize);
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par2 + i) == 0 || *(par2 + i) == 32)
                *(par2 + i) = '0';
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
        memcpy(temp + (size - inputsize), input, inputsize);
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par2 + i) == 0 || *(par2 + i) == 32)
                *(par2 + i) = '0';
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
        memcpy(temp + (size - inputsize), input, inputsize);
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
        char* par2 = (char*)malloc(size + 1);
        memcpy(par2, condition + 4 + size + 1, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par2 + i) == 0 || *(par2 + i) == 32)
                *(par2 + i) = '0';
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
        memcpy(temp + (size - inputsize), input, inputsize);
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        char* par1 = (char*)malloc(size + 1);
        memcpy(par1, condition + 4, size + 1);
        for (int i = 0; i < size; i++)
            if (*(par1 + i) == 0 || *(par1 + i) == 32)
                *(par1 + i) = '0';
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
        memcpy(temp + (size - inputsize), input, inputsize);
        for (int i = 0; i < size; i++)
            if (*(temp + i) == 0 || *(temp + i) == 32)
                *(temp + i) = '0';
        string paras(condition + 4, 4);
        int paranum = stringtoint(paras);
        char* par = (char*)malloc(size + 1);
        for (int i = 0; i < paranum; i++) {
            memcpy(par, condition + 8 + i * (size + 1), size + 1);
            for (int i = 0; i < size; i++)
                if (*(par + i) == 0 || *(par + i) == 32)
                    *(par + i) = '0';
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
