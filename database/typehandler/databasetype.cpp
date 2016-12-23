#include "databasetype.h"

DataBaseType::DataBaseType()
{
    size = 0;
    data = NULL;
    condition = NULL;
    NullCondition();
}
char* DataBaseType::getdata()
{
    return data;
}
void DataBaseType::printdata(string testinfo)
{
    cout << "Now begin " << testinfo << endl;
    for (int i = 0; i < size; i++) {
        int k = data[i];
        cout << "No." << i << " is: " << k << endl;
    }
    cout << "Now end " << testinfo << endl;
}
DataBaseType::~DataBaseType()
{
    if (data != NULL) {
        free(data);
        data = NULL;
    }
    if (condition != NULL) {
        free(condition);
        condition = NULL;
    }
}
bool DataBaseType::getNullable()
{
    return this->Nullable;
}
bool DataBaseType::getisNull()
{
    return this->isNull;
}
char* DataBaseType::getcondition()
{
    return this->condition;
}
int DataBaseType::getconditionsize()
{
    return this->conditionsize;
}
bool DataBaseType::readcondition(char* input, int inputsize, int& position)
{
    if (condition != NULL)
        free(condition);
    char* contype = (char*)malloc(4);
    memcpy(contype, input, 4);
    string scontype(contype, 4);
    free(contype);
    if (scontype == "FRTO" || scontype == "frTO" || scontype == "FRto" || scontype == "frto") {
        conditionsize = inputsize;
        condition = (char*)malloc(conditionsize);
        memcpy(condition, input, conditionsize);
        position += conditionsize;
    } else if (scontype == "NTEQ") {
        conditionsize = inputsize;
        condition = (char*)malloc(conditionsize);
        memcpy(condition, input, conditionsize);
        position += conditionsize;
    } else if (scontype == "CHOI") {
        int num;
        memcpy((char*)&num, input + 4, 4);
        cout << "scontype num=" << num << endl;
        conditionsize = inputsize;
        condition = (char*)malloc(conditionsize);
        memcpy(condition, input, conditionsize);
        position += conditionsize;
    } else if (scontype == "NULL") {
        conditionsize = 4;
        condition = (char*)malloc(conditionsize);
        memcpy(condition, input, conditionsize);
        position += conditionsize;
    } else {
        cout << "ERROR: NO CONDITION" << endl;
        NullCondition();
    }
    return true;
}
bool DataBaseType::writecondition(char* input, int& position)
{
    memcpy(input, condition, conditionsize);
    position += conditionsize;
    return true;
}
bool DataBaseType::readcondition(string* input)
{
    if (condition != NULL)
        free(condition);
    conditionsize = 0;
    if (input[0] == "FRTO" || input[0] == "frTO" || input[0] == "FRto" || input[0] == "frto") {
        int size1 = input[1].length();
        int size2 = input[2].length();
        conditionsize = size1 + size2 + 12;
        condition = (char*)malloc(conditionsize);
        memcpy(condition, input[0].data(), 4);
        memcpy(condition + 4, &size1, 4);
        memcpy(condition + 8, input[1].data(), size1);
        memcpy(condition + 8 + size1, &size2, 4);
        memcpy(condition + 12 + size1, input[2].data(), size2);
    } else if (input[0] == "NTEQ") {
        int size1 = input[1].length();
        conditionsize = size1 + 8;
        condition = (char*)malloc(conditionsize);
        memcpy(condition, input[0].data(), 4);
        memcpy(condition + 4, &size1, 4);
        memcpy(condition + 8, input[1].data(), size1);
    } else if (input[0] == "CHOI") {
        char* tmp = (char*)malloc(4);
        memcpy(tmp, input[1].data(), 4);
        int num = chartoint(tmp);
        conditionsize = 8;
        for (int i = 0; i < num; i++) {
            conditionsize += input[i + 2].length() + 4;
        }
        condition = (char*)malloc(conditionsize);
        memset(condition, 0, conditionsize);
        memcpy(condition, input[0].data(), 4);
        memcpy(condition + 4, input[1].data(), 4);
        int index = 8;
        for (int i = 0; i < num; i++) {
            int sizei = input[i + 2].length();
            memcpy(condition + index, &sizei, 4);
            index += 4;
            memcpy(condition + index, input[i + 2].data(), input[i + 2].length());
            index += input[i + 2].length();
        }
    } else if (input[0] == "NULL") {
        NullCondition();
    } else {
        cout << "ERROR: Not a condition will be null." << endl;
        NullCondition();
    }
    return true;
}
void DataBaseType::initialize(DataBaseType* input)
{
    this->conditionsize = input->getconditionsize();
    this->size = input->getRealSize();
    this->Nullable = input->getNullable();
    this->isNull = input->getisNull();
    if (this->data != NULL)
        free(this->data);
    if (this->condition != NULL)
        free(this->condition);
    this->condition = (char*)malloc(this->conditionsize);
    memcpy(this->condition, input->getcondition(), this->conditionsize);
    this->data = (char*)malloc(this->size + 1);
    memcpy(this->data, input->getdata(), this->size + 1);
}
int DataBaseType::stringtoint(string text)
{
    std::stringstream ss;
    int number;
    ss << text;
    ss >> number;
    return number;
}
void DataBaseType::NullCondition()
{
    if (this->condition != NULL)
        free(this->condition);
    this->condition = (char*)malloc(4);
    condition[0] = 'N';
    condition[1] = 'U';
    condition[2] = 'L';
    condition[3] = 'L';
    this->conditionsize = 4;
}
int DataBaseType::compare(char* source, int sourcelength, char* dest, int destlength)
{
    if (sourcelength > destlength)
        return 1;
    if (sourcelength < destlength)
        return -1;
    for (int i = 0; i < sourcelength; i++) {
        if (source[i] > dest[i])
            return 1;
        else if (source[i] < dest[i])
            return -1;
    }
    return 0;
}
int DataBaseType::chartoint(char* s1)
{
    int k = 0;
    memcpy(&k, s1, 4);
    return k;
}
