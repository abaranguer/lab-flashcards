#include <iostream>
#include <string>
#include <cstring>
#include <sqlite3.h>
#include "AnswerDAO.h"
#include "AnswerEntity.h"

using namespace std;

AnswerDAO::AnswerDAO()
{
    // TODO ctor
}

AnswerDAO::~AnswerDAO()
{
    // TODO dtor
}

bool AnswerDAO::existAnswerById(sqlite3 *conn, int id)
{
    int rc;
    int numOfRows = 0;
    bool retValue = false;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT COUNT(*) FROM ANSWER WHERE ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, id);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        numOfRows = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    if (numOfRows > 0) retValue = true;

    return retValue;
}

AnswerEntity* AnswerDAO::getAnswerById(sqlite3 *conn, int id)
{
    int rc;

    /* clean answer */
    answer.id = 0;
    answer.answer = "";

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, ANSWER FROM ANSWER WHERE ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, id);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        answer.id = sqlite3_column_int(stmt, 0);
        answer.answer = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    }
    else
    {
        cerr << "SELECT no data found: " << sqlite3_errmsg(conn) << endl;
        answer.id = -1;
        answer.answer = "";
    }

    sqlite3_finalize(stmt);

    return &answer;
}

AnswerEntity *AnswerDAO::getLastInsertedAnswer(sqlite3 *conn)
{
    int rc;

    /* clean answer */
    answer.id = 0;
    answer.answer = "";

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, ANSWER FROM ANSWER WHERE ID = (SELECT MAX(ID) FROM ANSWER);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        answer.id = sqlite3_column_int(stmt, 0);
        answer.answer = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    }
    else
    {
        cerr << "SELECT step failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);

    return &answer;
}

void AnswerDAO::addAnswer(sqlite3 *conn, AnswerEntity answerParam)
{
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "INSERT INTO ANSWER(ANSWER) VALUES (?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    const char *answerText = answerParam.answer.c_str();
    size_t lengthAnswerText = strlen(answerText);
    rc = sqlite3_bind_text(stmt, 1, answerText, lengthAnswerText, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "INSERT execute failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);
}

void AnswerDAO::updateAnswer(sqlite3 *conn, AnswerEntity answerParam)
{
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "UPDATE ANSWER SET ANSWER = ? WHERE ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "UPDATE prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    const char *answerText = answerParam.answer.c_str();
    size_t lengthAnswerText = strlen(answerText);
    rc = sqlite3_bind_text(stmt, 1, answerText, lengthAnswerText, NULL);
    rc = sqlite3_bind_int(stmt, 2, answerParam.id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "UPDATE execute failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);
}

void AnswerDAO::deleteAnswer(sqlite3 *conn, AnswerEntity answerParam)
{
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "DELETE FROM ANSWER WHERE ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "DELETE prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, answerParam.id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "DELETE execute failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);
}
