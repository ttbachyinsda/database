//
// Created by jameshuang on 16-12-10.
//

#include "ramiterator.h"

bool RamIterator::nextrow() {
    return false;
}

bool RamIterator::access(int pagenum, int rownum) {
    return false;
}

bool RamIterator::getdata(char *output, int &outputsize) {
    return false;
}

int RamIterator::getcurrentsize() {
    return 0;
}

bool RamIterator::getdata(Record *rec) {
    return false;
}

bool RamIterator::available() {
    return false;
}

bool RamIterator::deletedata() {
    return false;
}

bool RamIterator::insertdata(Record *rec) {
    return false;
}

void RamIterator::getbegin() {

}
