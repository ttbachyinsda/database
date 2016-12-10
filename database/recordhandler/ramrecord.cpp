//
// Created by jameshuang on 16-12-10.
//

#include "ramrecord.h"

void RamRecord::Initialize(DataBaseType **inidata, int datasize) {

}

void RamRecord::Input(char *input) {

}

bool RamRecord::getAt(int num, char *returndata, int &returndatasize) {
    return false;
}

string RamRecord::getAt(int num) {
    return nullptr;
}

bool RamRecord::set(string *input) {
    return false;
}

bool RamRecord::set(char **input, int *inputlen) {
    return false;
}

bool RamRecord::setAt(int wz, string input, bool isnull) {
    return false;
}

void RamRecord::update() {

}

int RamRecord::getMaxSize() {
    return 0;
}
