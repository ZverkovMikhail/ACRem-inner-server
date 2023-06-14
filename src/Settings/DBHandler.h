#ifndef DBHandler_h
#define DBHandler_h
#include <sqlite3.h>
#include "SPIFFS.h"
#include <FS.h>
#include "SettingsHandler.h"

typedef std::function<void(const char* jsonVals)> jsonValsCallback;

class DBHandler
{
private:
    sqlite3 *db;
    char *zErrMsg = 0;
    int db_open(const char *filename, sqlite3 **db); 
    int tableSettingsExists(sqlite3 *db);
    int createTableSettings(sqlite3 *db);

    // int db_exec(sqlite3 *db, const char *sql);
public:
    void init_db();
    void removeDB();
    int setInitSettings(const char* key);
    int setDefaultSettings(const char* key);
    void getSettingValues(const char *key,  jsonValsCallback *callback);
    void setSettingValues(const char *key, const char *vals);
};

extern DBHandler DB;
#endif