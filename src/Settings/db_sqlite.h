// #include <sqlite3.h>
// #include "SPIFFS.h"
// #include <FS.h>

// class Db
// {
// public:
//     void init_db()
//     {

//         if (!SPIFFS.begin(true))
//         {
//             Serial.println("Не удалось смонтировать файловую систему");
//             return;
//         }
//         // SPIFFS.remove("/ACdb.db"); // удаление БД

//         sqlite3_initialize();

//         if (db_open("/spiffs/ACdb.db", &db))
//             return;

//         int rc = tableStatusExists(db);
//         if (rc != SQLITE_OK)
//         {
//             rc = createTableStatus(db);
//             if (rc != SQLITE_OK)
//             {
//                 sqlite3_close(db);
//                 return;
//             }
//         }
//         sqlite3_close(db);
//     }

//     ACStatus db_get_status()
//     {

//         db_open("/spiffs/ACdb.db", &db);

//         int rc = sqlite3_exec(db, "SELECT * FROM Status WHERE id=1", callback_status, (void *)data, &zErrMsg);
//         if (rc != SQLITE_OK)
//         {
//             Serial.printf("SQL error: %s\n", zErrMsg);
//             sqlite3_free(zErrMsg);
//         }
//         else
//         {
//             Serial.printf("Статус с базы данных получен успешно\n");
//         }
//         return db_status;

//         sqlite3_close(db);
//     }

// private:

//     ACStatus db_status;
//     sqlite3 *db;
//     const char *data = "Callback function called";
//     char *zErrMsg = 0;

//     static int callback_status(void *data, int argc, char **argv, char **azColName)
//     {
//         ACStatus _status;
//         char *power;
//         char *mode;
//         _status.temp = 25;
//         ACHand.setStatus(_status);
//         ACStatus s = ACHand.getStatus();
//         s.print();
//         char *fun;
//         char *swing_v;
//         int save_start;
//         int i;
//         for (i = 0; i < argc; i++)
//         {
//             if (!strcmp(azColName[i], "power"))
//             {
//                 power = argv[i];
//             }

//             if (!strcmp(azColName[i], "mode"))
//             {
//                 mode = argv[i];
//             }

//             if (!strcmp(azColName[i], "temper"))
//             {
//                 // temper = atoi(argv[i]);
//             }

//             if (!strcmp(azColName[i], "fun"))
//             {
//                 fun = argv[i];
//             }

//             if (!strcmp(azColName[i], "swing_v"))
//             {
//                 swing_v = argv[i];
//             }

//             if (!strcmp(azColName[i], "save_start"))
//             {
//                 save_start = atoi(argv[i]);
//             }
//         }

//        // db_status.temp = temper;
//         return 0;
//     }

 
        

    

//     static int callback_print(void *data, int argc, char **argv, char **azColName)
//     {
//         int i;
//         Serial.printf("%d: ", (const char *)data);
//         for (i = 0; i < argc; i++)
//         {
//             Serial.printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//         }
//         Serial.printf("\n");
//         return 0;
//     }

//     int db_open(const char *filename, sqlite3 **db)
//     {
//         int rc = sqlite3_open(filename, db);
//         if (rc)
//         {
//             Serial.printf("Ошибка доступа к базе данных: %s\n", sqlite3_errmsg(*db));
//             return rc;
//         }
//         else
//         {
//             Serial.printf("База данных открыта\n");
//         }
//         return rc;
//     }

//     int tableStatusExists(sqlite3 *db)
//     {

//         int rc = sqlite3_exec(db, "SELECT COUNT(*) FROM Status WHERE id = 1", callback_print, (void *)data, &zErrMsg);
//         if (rc != SQLITE_OK)
//         {
//             Serial.printf("Таблицы Status не существует\n");
//             sqlite3_free(zErrMsg);
//         }
//         else
//         {
//             Serial.printf("Таблица Status существует\n");
//         }
//         return rc;
//     }

//     int createTableStatus(sqlite3 *db)
//     {

//         int rc = sqlite3_exec(db, "CREATE TABLE Status (id INTEGER, power TEXT, mode TEXT, temper INTEGER, fun TEXT, swing_v TEXT, save_start INTEGER);", callback_print, (void *)data, &zErrMsg);
//         if (rc != SQLITE_OK)
//         {
//             Serial.printf("Не удалост создать таблицу Status: %s\n", zErrMsg);
//             sqlite3_free(zErrMsg);
//         }
//         else
//         {
//             Serial.printf("Таблица Status создана\n");
//             rc = sqlite3_exec(db, "INSERT INTO Status VALUES (1,'off', 'Cool',25,'Quiet','Auto_swing',0);", callback_print, (void *)data, &zErrMsg);
//             if (rc != SQLITE_OK)
//             {
//                 Serial.printf("Не удалост наполнить таблицу Status: %s\n", zErrMsg);
//                 sqlite3_free(zErrMsg);
//             }
//             else
//             {
//                 Serial.printf("Таблица Status наполнена начальными данными\n");
//             }
//         }
//         return rc;
//     }
// };

// /*
// int db_exec(sqlite3 *db, const char *sql)
// {
//     Serial.println(sql);

//     int rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
//     if (rc != SQLITE_OK)
//     {
//         Serial.printf("SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     }
//     else
//     {
//         Serial.printf("Операция с базой данных успешна\n");
//     }
//     return rc;
// }*/

// /*

// Status callback_status(void *data, int argc, char **argv, char **azColName)
// {
//     int i;
//    // Serial.printf("%s: ", (const char *)data);
//     Status status;
//     for (i = 0; i < argc; i++)
//     {

//         Serial.printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

//         switch (azColName[i])
//         {
//         case "mode":
//              Serial.printf("MODE = %s\n", argv[i] ? argv[i] : "NULL");
//             break;

//         default:
//             break;
//         }
//     }
//     Serial.printf("\n");
//     return status;
// }



//    // rc = db_exec(db, "SELECT * FROM Status");

// */
