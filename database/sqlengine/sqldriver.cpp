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
    if (!checkEncrypted()) return false;
    if (currentDatabase == 0) {
        addErrorMessage("No database is selected when inserting into table "
                                + tableName);
        return false;
    }
    Table* myTable = currentDatabase->getTableByName(tableName);
    if (myTable == 0) {
        addErrorMessage("Table " + tableName + " does not exist.");
        return false;
    }
    int insertColID = myTable->getColumnIndexByName(columnName);
    if (insertColID != 1 || myTable->getcolumns()[columnName]->getType()[6] != 'B') {
        addErrorMessage("Target column does not exist or is not varbinary type!");
        return false;
    }
    ifstream in(inputFilename, ios::in | ios::binary);
    istreambuf_iterator<char> beg(in), end;
    string fileBuffer(beg, end);
    in.close();

    int storeOffset = BulbFile::put(fileBuffer.data(), fileBuffer.length());

    memcpy(data, &this->nowoffset, 4);
    int strsize = input.length();
    memcpy(data + 4, &strsize, 4);

    data[this->size] = IS_NOT_NULL;
    this->isNull = false;
}

bool SQLDriver::getBinaryFile(const string &tableName, const string &filename)
{
    if (isNull)
        return "NULL__DATA";
    if (this->nowoffset == -1)
        return "";
    int strsize;
    memcpy(&strsize, data + 4, 4);
    return BulbFile::get(this->nowoffset, strsize);
}
