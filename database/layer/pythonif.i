%module thjdb
%include "std_string.i"
%{
#include "pythonif.h"
extern void beginpythontest();
extern bool open();
extern bool close();
extern std::string execSQL(const std::string& sql);
%}
#include "pythonif.h"
extern void beginpythontest();
extern bool open();
extern bool close();
extern std::string execSQL(const std::string& sql);
