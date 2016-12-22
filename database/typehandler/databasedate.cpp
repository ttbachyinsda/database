#include "databasedate.h"

DatabaseDate::DatabaseDate()
{
    NullCondition();
    this->size = 8;
    data = (char*)malloc(size + 1);
    memset(data, 0, size + 1);
    data[size] = IS_NOT_NULL;
    this->Nullable = true;
    this->isNull = false;
}
DatabaseDate::DatabaseDate(bool cannull)
{
    NullCondition();
    this->size = 8;
    data = (char*)malloc(size + 1);
    memset(data, 0, size + 1);
    data[size] = IS_NOT_NULL;
    this->Nullable = cannull;
    this->isNull = false;
}
int DatabaseDate::getSize()
{
    return this->size + 1;
}
int DatabaseDate::getRealSize()
{
    return this->size;
}
int DatabaseDate::getMaxSize()
{
    return this->size + 1;
}
/* Don't try to use it in a public method. Try to use checkRight or
 * checkRightAndChange instead.
 * */
void DatabaseDate::change(string input)
{
    isNull = false;
    memcpy(data, input.data(), this->size);
    data[this->size] = IS_NOT_NULL;
    this->isNull = false;
}
void DatabaseDate::change(char* input, int size)
{
    isNull = false;
    memcpy(data, input, this->size);
    data[this->size] = IS_NOT_NULL;
    this->isNull = false;
}
void DatabaseDate::changetoNull()
{
    isNull = true;
    data[this->size] = IS_NULL;
}

/* Lintly commend to use these two methods
 * */
bool DatabaseDate::checkRight(string input)
{
    int lengthofinput = input.length();
    if (lengthofinput > this->size)
        return false;
    return analysis(input);
}
bool DatabaseDate::checkRight(string input, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    int lengthofinput = input.length();
    if (lengthofinput > this->size)
        return false;
    return analysis(input);
}
bool DatabaseDate::checkRightAndChange(string input)
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
bool DatabaseDate::checkRightAndChange(string input, bool inputisnull)
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
bool DatabaseDate::checkRightc(char* input, int size)
{
    if (size > this->size)
        return false;
    return analysisc(input, size);
}
bool DatabaseDate::checkRightc(char* input, int size, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    if (size > this->size)
        return false;
    return analysisc(input, size);
}
bool DatabaseDate::checkRightAndChangec(char* input, int size)
{
    bool can = checkRightc(input, size);
    if (can) {
        change(input, size);
        return true;
    }
    return false;
}
bool DatabaseDate::checkRightAndChangec(char* input, int size, bool inputisnull)
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
string DatabaseDate::getType()
{
    return "Type: Date";
}
string DatabaseDate::output()
{
    if (isNull)
        return "NULL__DATA";
    char* temp = (char*)malloc(this->size);
    memcpy(temp, data, this->size);
    string s(temp, this->size);
    free(temp);
    return s;
}

/* Don't delete that
 * */
DatabaseDate::~DatabaseDate()
{
}
bool DatabaseDate::read(char* input, int inputlen, int& position)
{
    memcpy(data, input, this->size + 1);
    position += this->size + 1;
    if (data[this->size] == IS_NULL)
        this->isNull = true;
    else
        this->isNull = false;
    return true;
}
bool DatabaseDate::write(char* input, int& position)
{
    memcpy(input, data, this->size + 1);
    position += this->size + 1;
    return true;
}
bool DatabaseDate::analysis(string input)
{
    string analysistype(condition, 4);
    if (analysistype == "NULL")
        return true;
    if (analysistype == "FRTO") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);

        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);

        time_point<system_clock, chrono::nanoseconds> par2tp;
        memcpy(&par2tp, par2, 8);

        free(par1);
        free(par2);

        if (parinput >= par1tp && parinput <= par2tp)
            return true;
        else
            return false;
    }
    if (analysistype == "frTO") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        time_point<system_clock, chrono::nanoseconds> par2tp;
        memcpy(&par2tp, par2, 8);

        free(par1);
        free(par2);

        if (parinput > par1tp && parinput <= par2tp)
            return true;
        else
            return false;
    }
    if (analysistype == "FRto") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        time_point<system_clock, chrono::nanoseconds> par2tp;
        memcpy(&par2tp, par2, 8);

        free(par1);
        free(par2);

        if (parinput >= par1tp && parinput < par2tp)
            return true;
        else
            return false;
    }
    if (analysistype == "frto") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        time_point<system_clock, chrono::nanoseconds> par2tp;
        memcpy(&par2tp, par2, 8);

        free(par1);
        free(par2);

        if (parinput > par1tp && parinput < par2tp)
            return true;
        else
            return false;
    }
    if (analysistype == "NTEQ") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        free(par1);

        if (par1tp != parinput)
            return true;
        else
            return false;
    }
    if (analysistype == "CHOI") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input.data(), 8);

        int paranum = chartoint(condition + 4);
        char* par = (char*)malloc(size);
        int index = 8;
        for (int i = 0; i < paranum; i++) {
            int sizei = chartoint(condition + index);
            index += 4;
            memcpy(par, condition + index, sizei);
            index += sizei;

            time_point<system_clock, chrono::nanoseconds> pariLint;
            memcpy(&pariLint, par, 8);
            if (pariLint == parinput) {
                free(par);
                return true;
            }
        }
        free(par);
        return false;
    }
    cout << "ERROR: No condition will be NUll" << endl;
    NullCondition();
    return true;
}
bool DatabaseDate::analysisc(char* input, int inputsize)
{
    string analysistype(condition, 4);
    if (analysistype == "NULL")
        return true;
    if (analysistype == "FRTO") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        time_point<system_clock, chrono::nanoseconds> par2tp;
        memcpy(&par2tp, par2, 8);

        free(par1);
        free(par2);

        if (parinput >= par1tp && parinput <= par2tp)
            return true;
        else
            return false;
    }
    if (analysistype == "frTO") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        time_point<system_clock, chrono::nanoseconds> par2tp;
        memcpy(&par2tp, par2, 8);

        free(par1);
        free(par2);

        if (parinput > par1tp && parinput <= par2tp)
            return true;
        else
            return false;
    }
    if (analysistype == "FRto") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        time_point<system_clock, chrono::nanoseconds> par2tp;
        memcpy(&par2tp, par2, 8);

        free(par1);
        free(par2);

        if (parinput >= par1tp && parinput < par2tp)
            return true;
        else
            return false;
    }
    if (analysistype == "frto") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        time_point<system_clock, chrono::nanoseconds> par2tp;
        memcpy(&par2tp, par2, 8);

        free(par1);
        free(par2);

        if (parinput > par1tp && parinput < par2tp)
            return true;
        else
            return false;
    }
    if (analysistype == "NTEQ") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        time_point<system_clock, chrono::nanoseconds> par1tp;
        memcpy(&par1tp, par1, 8);

        free(par1);

        if (parinput != par1tp)
            return true;
        else
            return false;
    }
    if (analysistype == "CHOI") {
        time_point<system_clock, chrono::nanoseconds> parinput;
        memcpy(&parinput, input, 8);

        int paranum = chartoint(condition + 4);
        char* par = (char*)malloc(size);
        int index = 8;
        for (int i = 0; i < paranum; i++) {
            int sizei = chartoint(condition + index);
            index += 4;
            memcpy(par, condition + index, sizei);
            index += sizei;

            time_point<system_clock, chrono::nanoseconds> pariLint;
            memcpy(&pariLint, par, 8);
            if (pariLint == parinput) {
                free(par);
                return true;
            }
        }
        free(par);
        return false;
    }
    cout << "ERROR: No condition will be NUll" << endl;
    NullCondition();
    return true;
}
