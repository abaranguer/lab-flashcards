#include "Database.h"

#include <sqlite3.h>
#include <string>
#include <iostream>

using namespace std;

Database::Database(string connString)
{
    const char *connStringAux = connString.c_str();
    int rc = sqlite3_open(connStringAux, &conn);

    if( rc != SQLITE_OK )
    {
        cout << "Can't open database: " << sqlite3_errmsg(conn) << endl;
    }
}

Database::~Database(void)
{
    sqlite3_close(Database::conn);
}

sqlite3* Database::getConn(void)
{
    return conn;
}

