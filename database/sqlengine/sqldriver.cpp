//
// Created by jameshuang on 16-10-19.
//

#include <sstream>
#include <iostream>
#include <unistd.h>
#include "sqldriver.h"

const std::string SQLDriver::systemName = "top";

SQLDriver::SQLDriver() {
    initialize();
}

SQLDriver::~SQLDriver() {
    clearPreviousSession();
    // current database will be deleted by the manager
    if (databaseManager) delete databaseManager;
    if (queryExecuter) delete queryExecuter;
}

/**
 * Execute a SQL command and returns whether it succeeded.
 * @param sqlStr
 * @return success or not
 */
bool SQLDriver::execute(const std::string& sqlStr) {
    clearPreviousSession();

    std::istringstream* sstream = new std::istringstream(sqlStr);
    sqlLexer = new yy::SQLLexer(sstream, this);
    sqlParser = new yy::SQLParser(*sqlLexer, *this);

    lastSucceeded = (sqlParser->parse() == 0);

    if (!lastSucceeded) return false;

    delete sstream;
    for (SQLAction* it : allActions) {
        it->setDriver(this);
        // Execute everthing before error prompt.
        lastSucceeded = it->execute();
        if (!lastSucceeded) return false;
    }

    return lastSucceeded;
}

void SQLDriver::encryptDatabaseManager(const string &password)
{
    if (!isEncrypted) {
        databaseManager->encrypt(password);
        currentDatabase = 0;
        isEncrypted = true;
    }
}

void SQLDriver::decryptDatabaseManager(const string &password)
{
    if (!isEncrypted) return;
//    databaseManager = new DatabaseManager();
//    databaseManager->setname(SQLDriver::systemName);
//    databaseManager->setfilename(SQLDriver::systemName + ".tdb");
//    int dbmInitResult = databaseManager->Initialize();
//    if (dbmInitResult == -1) {
//        isEncrypted = true;
//        delete databaseManager;
//        databaseManager = 0;
//    }
    int decryptResult = databaseManager->decrypt(password);
    if (decryptResult == 0) return;
    isEncrypted = false;
    currentDatabase = 0;
    databaseManager->Initialize();
}

void SQLDriver::clearPreviousSession() {
    if (sqlLexer)  delete sqlLexer;
    if (sqlParser) delete sqlParser;
    if (result) delete result;
    result = 0;
    sqlLexer = 0;
    sqlParser = 0;
    warningMessages.clear();
    errorMessages.clear();
    for (std::vector<SQLAction*>::iterator it = allActions.begin();
         it != allActions.end(); ++ it) {
        delete (*it);
    }
    allActions.clear();
    lastAffectedRows = 0;
    lastHasResult = false;
}

void SQLDriver::initialize()
{
    sqlLexer  = 0;
    sqlParser = 0;
    lastSucceeded = false;
    lastHasResult = false;
    lastAffectedRows = 0;
    currentDatabase = 0;
    result = 0;

    // May consider lazy init.
    databaseManager = new DatabaseManager();
    databaseManager->setname(SQLDriver::systemName);
    databaseManager->setfilename(SQLDriver::systemName + ".tdb");
    queryExecuter = new QueryExecutor(this);
    // If file not exist, new file will be created.
    BulbFile::setfilename("bulbfile.bin");

    int dbmInitResult = databaseManager->Initialize();
    isEncrypted = (dbmInitResult == -1);

}

SQLDriver::SQLDriver(const string &workingDir) {
    int chdirRes = chdir(workingDir.c_str());
    if (chdirRes == -1) {
        cout << "Fatal: " << workingDir << " : Permission denined." << endl;
        exit(0);
    }
    initialize();
}

void SQLDriver::setWorkingDir(const std::string &workingDir) {
    clearPreviousSession();
    // current database will be deleted by the manager
    if (databaseManager) delete databaseManager;
    delete queryExecuter;
    int chdirRes = chdir(workingDir.c_str());
    if (chdirRes == -1) {
        cout << "Fatal: " << workingDir << " : Permission denined." << endl;
        exit(0);
    }
    initialize();
}

bool SQLDriver::storeBinaryFile(const string& tableName, const string& primaryKey,
                                const string &inputFilename)
{
    clearPreviousSession();
    if (isEncrypted) return false;
    if (currentDatabase == 0) {
        addErrorMessage("No database is selected when inserting into table "
                                + tableName);
        lastSucceeded = false;
        return false;
    }
    Table* myTable = currentDatabase->getTableByName(tableName);
    if (myTable == 0) {
        addErrorMessage("Table " + tableName + " does not exist.");
        lastSucceeded = false;
        return false;
    }
    db_index* myTableIndex = myTable->getindexes()[0];

    if (myTable->getcolumns()[1]->getType()[6] != 'B' || myTableIndex == 0) {
        addErrorMessage("The table does not support binary file storage.");
        lastSucceeded = false;
        return false;
    }

    // Change to std interface
    if (access(inputFilename.c_str(), 0) == -1) {
        addErrorMessage("The file does not exist.");
        lastSucceeded = false;
        return false;
    }

    int fm = open(inputFilename.c_str(), PARA);
    int totalsize = Encrypt::get_file_size(inputFilename.c_str());

    char* buf = new char[totalsize];
    read(fm, (void*) buf, totalsize);

    close(fm);
    string fileBuffer(buf, totalsize);
    delete[] buf;

    Iterator* iter = IteratorFactory::getiterator(myTable);
    Record* rec = RecordFactory::getrecord(myTable);

    vector<pair<int, int> > fRes;
    myTableIndex->findAll(SQLOperand::EQUAL, iter->compile(primaryKey, 0), &fRes);

    if (fRes.size() != 0) {
        addErrorMessage("The primary key is duplicated.");
        delete iter; delete rec;
        lastSucceeded = false;
        return false;
    }

    int storeOffset = BulbFile::put(fileBuffer.data(), fileBuffer.length());
    char data[8];
    memcpy(data, &storeOffset, 4);
    int strsize = fileBuffer.length();
    memcpy(data + 4, &strsize, 4);
    string dataStr(data, 8);
    rec->setAt(0, primaryKey, false);
    rec->setAt(1, dataStr, false);
    rec->update();

    int dum;
    myTable->FastAllInsert(dum, dum, rec);

    delete iter;
    delete rec;
    lastSucceeded = true;
    return true;
}

bool SQLDriver::getBinaryFile(const string &tableName, const string& primaryKey,
                              const string &outputFilename)
{
    clearPreviousSession();
    if (isEncrypted) return false;
    if (currentDatabase == 0) {
        addErrorMessage("No database is selected when inserting into table "
                                + tableName);
        lastSucceeded = false;
        return false;
    }
    Table* myTable = currentDatabase->getTableByName(tableName);
    if (myTable == 0) {
        addErrorMessage("Table " + tableName + " does not exist.");
        lastSucceeded = false;
        return false;
    }
    db_index* myTableIndex = myTable->getindexes()[0];

    if (myTable->getcolumns()[1]->getType()[6] != 'B' || myTableIndex == 0) {
        addErrorMessage("The table does not support binary file storage.");
        lastSucceeded = false;
        return false;
    }

    Iterator* iter = IteratorFactory::getiterator(myTable);
    Record* rec = RecordFactory::getrecord(myTable);

    vector<pair<int, int> > fRes;
    myTableIndex->findAll(SQLOperand::EQUAL, iter->compile(primaryKey, 0), &fRes);

    if (fRes.size() != 1) {
        addErrorMessage("The primary key does not exist");
        delete iter; delete rec;
        lastSucceeded = false;
        return false;
    }

    iter->access(fRes[0].first, fRes[0].second);
    iter->getdata(rec);

    string dataRef = rec->getAt(1);
    int offset, strsize;
    memcpy(&offset, dataRef.data(), 4);
    memcpy(&strsize, (char*)dataRef.data() + 4, 4);
    string fileContent = BulbFile::get(offset, strsize);

    remove(outputFilename.c_str());
    FILE* f = fopen(outputFilename.c_str(), "ab+");
    fclose(f);

    int fm = open(outputFilename.c_str(), PARA);
    write(fm, fileContent.data(), fileContent.size());
    close(fm);

    delete iter;
    delete rec;
    lastSucceeded = true;
    return true;

}
