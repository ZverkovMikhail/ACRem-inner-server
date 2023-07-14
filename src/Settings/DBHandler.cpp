#include "DBHandler.h"

// auto callback_print = [](void *data, int argc, char **argv, char **azColName)->int {
//                  int i;
//                  Serial.printf("callback_print YO-YO!!!\n");
//                 Serial.printf("%d: ", (const char *)data);
//                 for (i = 0; i < argc; i++)
//                 {
//                     Serial.printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//                 }
//                 Serial.printf("\n");
//         return 0;
//             };
// const char* callback_data = "Callback function called";

int DBHandler::db_open(const char *filename, sqlite3 **db){
    
    int rc = sqlite3_open(filename, db);    
        
            Serial.printf("DBHandler::db_open %s статус: %d\n", sqlite3_errmsg(*db), rc);
        if (rc != SQLITE_OK)
        {
            Serial.printf("Ошибка доступа к базе данных: %s статус: %d\n", sqlite3_errmsg(*db), rc);
            return rc;
        }
        else
        {
            Serial.printf("База данных открыта\n");
        }
        return rc;
}
void DBHandler::init_db(){
    if (!SPIFFS.begin(true))
        {
            Serial.println("Не удалось смонтировать файловую систему");
            return;
        }
        
        sqlite3_initialize();
        int rc = db_open("/spiffs/ACdb.db", &db);
        if (rc == SQLITE_OK){
            rc = tableSettingsExists(db, "wifi");
            if (rc != SQLITE_OK){
                rc = createTableSettings(db);
                rc = setInitSettings("wifi");
                sqlite3_close(db);
                return;
                }
            }
            tableSettingsExists(db, "mqtt");
        }

        
        // sqlite3_close(db);


void DBHandler::removeDB(){
    sqlite3_close(db);
    SPIFFS.begin(true);
    SPIFFS.remove("/ACdb.db");
    delay(500);
}
int DBHandler::tableSettingsExists(sqlite3 *db, const char *key){
        // int (DBHandler::*)(const char*);
        // func = setDefaultSettings;
        _keyBuf = key;
        sqlite3_callback _callback = [](void *data, int argc, char **argv, char **azColName)->int {
                char* count = argv[0];
                const char *key = ((DBHandler *) data)->_keyBuf;
                Serial.println(atoi(count));
                if (atoi(count) < 1){
                    ((DBHandler *) data)->setInitSettings(key);
                }
                
                return 0;
        };
        String sql = F("SELECT COUNT(*) FROM Settings WHERE key='");
        sql+=F(key);
        sql+=F("';");
        // int rc = sqlite3_exec(db, "SELECT COUNT(*) FROM Settings WHERE key = 'wifi';", _callback, (void *)this, &zErrMsg);
        int rc = sqlite3_exec(db, sql.c_str(), _callback, (void *)this, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            Serial.printf("Таблицы Settings не существует\n");
            sqlite3_free(zErrMsg);
        }
        else
        {
            Serial.printf("Таблица Settings существует\n");
        }
        return rc;    
}

int DBHandler::createTableSettings(sqlite3 *db){

        int rc = sqlite3_exec(db, "CREATE TABLE Settings (key TEXT, value TEXT);", NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            Serial.printf("Не удалост создать таблицу Settings: %s status: %d\n", zErrMsg, rc);
            sqlite3_free(zErrMsg);
        }
        else
        {
            Serial.printf("Таблица Settings создана\n");
        }
        return rc;
}

    void DBHandler::getSettingValues(const char *key,  jsonValsCallback *callback){
        String sql = F("SELECT value FROM Settings WHERE key='");
        sql+=F(key);
        sql+=F("';");
        sqlite3_callback _callback = [](void *data, int argc, char **argv, char **azColName)->int {
            jsonValsCallback *call = reinterpret_cast<jsonValsCallback*>(data);
            char* vals = argv[0];            
            Serial.print("vals = ");
            Serial.println(vals);
            (*call)(vals);
            return 0;  
        };
        Serial.print("DBHandler::getSettingValues = ");
        Serial.println(sql);
        int rc = sqlite3_exec(db, sql.c_str(), _callback, (void *)callback, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            Serial.print("DBHandler::getSettingValues status: ");
            Serial.print(rc);
            Serial.print(" error: ");
            Serial.println(zErrMsg);
            sqlite3_free(zErrMsg);
        }
    }

   void DBHandler::setSettingValues(const char *key, const char *vals){
    // "UPDATE Settings SET value = 'vals' WHERE key = 'key';"
        String sql = F("UPDATE Settings SET value = '");
        sql+=F(vals);
        sql+=F("' WHERE key = '");
        sql+=F(key);
        sql+=F("';");
        int rc = sqlite3_exec(db, sql.c_str(), NULL, (void *)NULL, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            Serial.print("DBHandler::setSettingValues status: ");
            Serial.print(rc);
            Serial.print(" error: ");
            Serial.println(zErrMsg);
            sqlite3_free(zErrMsg);
        }else{
             Serial.println("DBHandler::setSettingValues is done!!!");
        }
   }
   int DBHandler::setInitSettings(const char* key){
        int rc = -1;
        String json;
        Serial.print("DBHandler::setInitSettings = ");
        Serial.println(key);
        if (strcmp(key, "wifi") == 0){        
            WiFiSettings sett;
            sett.getDefault().getJsonStr(json);
            
        }else if (strcmp(key, "mqtt") == 0){
            MQTTSettings sett;
            sett.getDefault().getJsonStr(json);

        }
            String sql = F("INSERT INTO Settings VALUES ('");
            sql +=  key; 
            sql += F("', '");
            sql += json;
            sql += F("');");
    
            rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);

            if (rc != SQLITE_OK)
            {
                Serial.printf("Не удалост наполнить таблицу Settings: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                Serial.printf("Таблица Settings наполнена начальными данными\n");
            }
       
            return rc;
   }
   int DBHandler::setDefaultSettings(const char* key){
    int rc = -1;
    if (strcmp(key, "wifi") == 0){
            WiFiSettings sett;
            String json;
            sett.getDefault().getJsonStr(json);
            String sql = F("UPDATE Settings SET value = '");
            sql+=json;
            sql+=F("' WHERE key = '");
            sql+=F(key);
            sql+=F("';");
            Serial.printf("sql = %s\n", sql);
            rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);

            if (rc != SQLITE_OK)
            {
                Serial.printf("DBHandler::setDefaultSettings: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }       
    }
            return rc;
   }

DBHandler DB;