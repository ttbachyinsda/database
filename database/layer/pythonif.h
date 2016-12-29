#include "../databasehandler/bulbfile.h"
#include "../sqlengine/sqldriver.h"
#include "../tester/testflexible.h"
#include "json.hpp"

using json = nlohmann::json;
SQLDriver* driver = NULL;

void beginpythontest()
{
    testflexible t;
    t.begintest();
}

bool open()
{
    if (driver != NULL)
        return false;
    driver = new SQLDriver();
    return true;
}

bool close()
{
    if (driver)
        delete driver;
    driver = NULL;
    return true;
}

std::string execSQL(const std::string& sql)
{
    driver->execute(sql);

    json j;
    if (driver->getResult() != NULL)
        j["result"] = driver->getResult()->toJSON();
    for (const std::string& s : driver->getWarningMessages())
        j["warning"].push_back(s);
    for (const std::string& s : driver->getErrorMessages())
        j["error"].push_back(s);
    return j.dump();
}

std::string storeBinaryFile(const std::string& tableName, const std::string& primaryKey,
                            const std::string &inputFilename) {
    driver->storeBinaryFile(tableName, primaryKey, inputFilename);

    json j;
    if (driver->getResult() != NULL)
        j["result"] = driver->getResult()->toJSON();
    for (const std::string& s : driver->getWarningMessages())
        j["warning"].push_back(s);
    for (const std::string& s : driver->getErrorMessages())
        j["error"].push_back(s);
    return j.dump();
}

std::string getBinaryFile(const std::string& tableName, const std::string& primaryKey,
                          const std::string &outputFilename) {
    driver->getBinaryFile(tableName, primaryKey, outputFilename);

    json j;
    if (driver->getResult() != NULL)
        j["result"] = driver->getResult()->toJSON();
    for (const std::string& s : driver->getWarningMessages())
        j["warning"].push_back(s);
    for (const std::string& s : driver->getErrorMessages())
        j["error"].push_back(s);
    return j.dump();
}
