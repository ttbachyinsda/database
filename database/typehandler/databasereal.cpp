#include "databasereal.h"

DatabaseReal::DatabaseReal()
{
    NullCondition();
    this->size = 8;
    data = (char*)malloc(size + 1);
    memset(data, 0, size + 1);
    data[size] = IS_NOT_NULL;
    this->Nullable = true;
    this->isNull = false;
}
DatabaseReal::DatabaseReal(bool cannull)
{
    NullCondition();
    this->size = 8;
    data = (char*)malloc(size + 1);
    memset(data, 0, size + 1);
    data[size] = IS_NOT_NULL;
    this->Nullable = cannull;
    this->isNull = false;
}
int DatabaseReal::getSize()
{
    return this->size + 1;
}
int DatabaseReal::getRealSize()
{
    return this->size;
}
int DatabaseReal::getMaxSize()
{
    return this->size + 1;
}
/* Don't try to use it in a public method. Try to use checkRight or
 * checkRightAndChange instead.
 * */
void DatabaseReal::change(string input)
{
    isNull = false;
    memcpy(data, input.data(), this->size);
    data[this->size] = IS_NOT_NULL;
    this->isNull = false;
}
void DatabaseReal::change(char* input, int size)
{
    isNull = false;
    memcpy(data, input, this->size);
    data[this->size] = IS_NOT_NULL;
    this->isNull = false;
}
void DatabaseReal::changetoNull()
{
    isNull = true;
    data[this->size] = IS_NULL;
}

/* Really commend to use these two methods
 * */
bool DatabaseReal::checkRight(string input)
{
    int lengthofinput = input.length();
    if (lengthofinput > this->size)
        return false;
    return analysis(input);
}
bool DatabaseReal::checkRight(string input, bool inputisnull)
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
bool DatabaseReal::checkRightAndChange(string input)
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
bool DatabaseReal::checkRightAndChange(string input, bool inputisnull)
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
bool DatabaseReal::checkRightc(char* input, int size)
{
    if (size > this->size)
        return false;
    return analysisc(input, size);
}
bool DatabaseReal::checkRightc(char* input, int size, bool inputisnull)
{
    if (inputisnull && !Nullable)
        return false;
    if (inputisnull)
        return true;
    if (size > this->size)
        return false;
    return analysisc(input, size);
}
bool DatabaseReal::checkRightAndChangec(char* input, int size)
{
    bool can = checkRightc(input, size);
    if (can) {
        change(input, size);
        return true;
    }
    return false;
}
bool DatabaseReal::checkRightAndChangec(char* input, int size, bool inputisnull)
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
string DatabaseReal::getType()
{
    return "Type: REAL";
}
string DatabaseReal::output()
{
    if (isNull)
        return "NULL__DATA";
    double temp;
    memcpy(&temp, data, 8);
    stringstream ss;
    ss << temp;
    string s1 = ss.str();
    return s1;
}

/* Don't delete that
 * */
DatabaseReal::~DatabaseReal()
{
}
bool DatabaseReal::read(char* input, int inputlen, int& position)
{
    memcpy(data, input, this->size + 1);
    position += this->size + 1;
    if (data[this->size] == IS_NULL)
        this->isNull = true;
    else
        this->isNull = false;
    return true;
}
bool DatabaseReal::write(char* input, int& position)
{
    memcpy(input, data, this->size + 1);
    position += this->size + 1;
    return true;
}
bool DatabaseReal::analysis(string input)
{
    string analysistype(condition, 4);
    if (analysistype == "NULL")
        return true;
    if (analysistype == "FRTO") {
        double parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        double par2real;
        memcpy(&par2real, par2, 8);

        free(par1);
        free(par2);

        if (parinput >= par1real && parinput <= par2real)
            return true;
        else
            return false;
    }
    if (analysistype == "frTO") {
        double parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        double par2real;
        memcpy(&par2real, par2, 8);

        free(par1);
        free(par2);

        if (parinput > par1real && parinput <= par2real)
            return true;
        else
            return false;
    }
    if (analysistype == "FRto") {
        double parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        double par2real;
        memcpy(&par2real, par2, 8);

        free(par1);
        free(par2);

        if (parinput >= par1real && parinput < par2real)
            return true;
        else
            return false;
    }
    if (analysistype == "frto") {
        double parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        double par2real;
        memcpy(&par2real, par2, 8);

        free(par1);
        free(par2);

        if (parinput > par1real && parinput < par2real)
            return true;
        else
            return false;
    }
    if (analysistype == "NTEQ") {
        double parinput;
        memcpy(&parinput, input.data(), 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        free(par1);

        if (fabs(parinput - par1real) > 1e-9)
            return true;
        else
            return false;
    }
    if (analysistype == "CHOI") {
        double parinput;
        memcpy(&parinput, input.data(), 8);

        int paranum = chartoint(condition + 4);
        char* par = (char*)malloc(size);
        int index = 8;
        for (int i = 0; i < paranum; i++) {
            int sizei = chartoint(condition + index);
            index += 4;
            memcpy(par, condition + index, sizei);
            index += sizei;

            double parireal;
            memcpy(&parireal, par, 8);
            if (fabs(parireal - parinput) < 1e-9) {
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
bool DatabaseReal::analysisc(char* input, int inputsize)
{
    string analysistype(condition, 4);
    if (analysistype == "NULL")
        return true;
    if (analysistype == "FRTO") {
        double parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        double par2real;
        memcpy(&par2real, par2, 8);

        free(par1);
        free(par2);

        if (parinput >= par1real && parinput <= par2real)
            return true;
        else
            return false;
    }
    if (analysistype == "frTO") {
        double parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        double par2real;
        memcpy(&par2real, par2, 8);

        free(par1);
        free(par2);

        if (parinput > par1real && parinput <= par2real)
            return true;
        else
            return false;
    }
    if (analysistype == "FRto") {
        double parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        double par2real;
        memcpy(&par2real, par2, 8);

        free(par1);
        free(par2);

        if (parinput >= par1real && parinput < par2real)
            return true;
        else
            return false;
    }
    if (analysistype == "frto") {
        double parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        int size2 = chartoint(condition + 8 + size1);
        char* par2 = (char*)malloc(size2);
        memcpy(par2, condition + 12 + size1, size2);
        double par2real;
        memcpy(&par2real, par2, 8);

        free(par1);
        free(par2);

        if (parinput > par1real && parinput < par2real)
            return true;
        else
            return false;
    }
    if (analysistype == "NTEQ") {
        double parinput;
        memcpy(&parinput, input, 8);

        int size1 = chartoint(condition + 4);
        char* par1 = (char*)malloc(size1);
        memcpy(par1, condition + 8, size1);
        double par1real;
        memcpy(&par1real, par1, 8);

        free(par1);

        if (fabs(parinput - par1real) > 1e-9)
            return true;
        else
            return false;
    }
    if (analysistype == "CHOI") {
        double parinput;
        memcpy(&parinput, input, 8);

        int paranum = chartoint(condition + 4);
        char* par = (char*)malloc(size);
        int index = 8;
        for (int i = 0; i < paranum; i++) {
            int sizei = chartoint(condition + index);
            index += 4;
            memcpy(par, condition + index, sizei);
            index += sizei;

            double parireal;
            memcpy(&parireal, par, 8);
            if (fabs(parireal - parinput) < 1e-9) {
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
