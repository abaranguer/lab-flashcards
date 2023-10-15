#include <iostream>
#include <vector>
#include <cstring>
#include "BoxDAO.h"
#include "BoxEntity.h"

using namespace std;

BoxDAO::BoxDAO()
{
    // TODO ctor
}

BoxDAO::~BoxDAO()
{
    // TODO dtor
}

vector<BoxEntity> *BoxDAO::getAll(sqlite3 *conn)
{
    int rc;

    /* clean list */
    boxes.clear();

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, NAME FROM BOX;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        BoxEntity box;
        box.id = sqlite3_column_int(stmt, 0);
        box.name = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));

        boxes.push_back(box);
    }

    if (rc != SQLITE_DONE)
    {
        cerr << "SELECT failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);

    return &boxes;
}
