#include <stdio.h>
#include "C:/Users/Jason/CLionProjects/sqlite/sqlite3.h"

/** Callback for Creating Table and Inserting into Table **/
static int createTableAndInsertCallback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

/** Callback for Selecting Records from Table **/
/**
 *
 * @param data          4th parameter from sqlite3_exec()
 * @param argc          number of columns in the result
 * @param argv          array of pointers to strings obtained as if from sqlite3_column_text(), one for each column
 * @param azColName     array of pointers to strings where each entry represents the name of corresponding result column as obtained from sqlite3_column_name()
 * @return
 */
static int selectRecordsCallback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    /** Following is used for Selecting Records from Table **/
    const char* data = "Callback function called";
    /********************************************************/

    rc = sqlite3_open("C:\\Users\\Jason\\Temp\\test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

//    sql = "CREATE TABLE COMPANY("  \
//      "ID INT PRIMARY KEY     NOT NULL," \
//      "NAME           TEXT    NOT NULL," \
//      "AGE            INT     NOT NULL," \
//      "ADDRESS        CHAR(50)," \
//      "SALARY         REAL );";

    /************/
    /** Create **/
    /************/
//    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
//         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
//         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
//         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
//         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
//         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
//         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
//         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    /**********/
    /** Read **/
    /**********/
//    sql = "SELECT * FROM COMPANY";

    /************/
    /** Update **/
    /************/
//    sql = "UPDATE COMPANY set SALARY = 25000.00 WHERE ID=1; " \
//            "SELECT * FROM COMPANY";

    /************/
    /** Delete **/
    /************/
    sql = "DELETE FROM COMPANY WHERE ID=2; " \
            "SELECT * FROM COMPANY";

    /** Following is used for Creating Table and Inserting into Table **/
//    rc = sqlite3_exec(db, sql, createTableAndInsertCallback, 0, &zErrMsg);
    /********************************************************************/

    /********* Following is used for Selecting Records From Table *********/
    rc = sqlite3_exec(db, sql, selectRecordsCallback, (void*)data, &zErrMsg);
    /**********************************************************************/

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
//        fprintf(stdout, "Table created successfully\n");
//        fprintf(stdout, "Records created successfully\n");
        fprintf(stdout, "Operation completed successfully\n");
    }
    sqlite3_close(db);
    return 0;
}