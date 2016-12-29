%module thjdb
%include "std_string.i"
%{
#include "pythonif.h"
extern void beginpythontest();
extern bool open();
extern bool close();
extern std::string execSQL(const std::string& sql);
extern std::string storeBinaryFile(const std::string& tableName, const std::string& primaryKey,
                                   const std::string &inputFilename);
extern std::string getBinaryFile(const std::string& tableName, const std::string& primaryKey,
                                 const std::string &outputFilename);
%}
#include "pythonif.h"
extern void beginpythontest();
extern bool open();
extern bool close();
extern std::string execSQL(const std::string& sql);
extern std::string storeBinaryFile(const std::string& tableName, const std::string& primaryKey,
                                   const std::string &inputFilename);
extern std::string getBinaryFile(const std::string& tableName, const std::string& primaryKey,
                                 const std::string &outputFilename);
