#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>

using namespace std;

class Database
{
public:
    Database(string dbUrl);
    ~Database(void);
    sqlite3 *getConn(void);

private:
    sqlite3 *conn;
};

#endif // DATABASE_H
