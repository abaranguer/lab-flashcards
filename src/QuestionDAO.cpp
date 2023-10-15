#include <iostream>
#include <string>
#include <cstring>
#include <sqlite3.h>
#include "QuestionDAO.h"
#include "QuestionEntity.h"

using namespace std;

QuestionDAO::QuestionDAO()
{
    // TODO ctor
}

QuestionDAO::~QuestionDAO()
{
    // TODO dtor
}

bool QuestionDAO::existQuestionById(sqlite3 *conn, int id)
{
    int rc;
    int numOfRows = 0;
    bool retValue = false;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT COUNT(*) FROM QUESTION WHERE ID = ?;", -1, &stmt, NULL);
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

QuestionEntity* QuestionDAO::getQuestionById(sqlite3 *conn, int id)
{
    int rc;

    /* clean question */
    question.id = 0;
    question.question = "";

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, QUESTION FROM QUESTION WHERE ID = ?;", -1, &stmt, NULL);
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
        question.id = sqlite3_column_int(stmt, 0);
        question.question = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    }
    else
    {
        cerr << "SELECT no data found: " << sqlite3_errmsg(conn) << endl;
        question.id = -1;
        question.question = "";
    }

    sqlite3_finalize(stmt);

    return &question;
}

QuestionEntity *QuestionDAO::getLastInsertedQuestion(sqlite3 *conn)
{
    int rc;

    /* clean question */
    question.id = 0;
    question.question = "";

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, QUESTION FROM QUESTION WHERE ID = (SELECT MAX(ID) FROM QUESTION);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        question.id = sqlite3_column_int(stmt, 0);
        question.question = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    }
    else
    {
        cerr << "SELECT step failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);

    return &question;
}

void QuestionDAO::addQuestion(sqlite3 *conn, QuestionEntity questionParam)
{
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "INSERT INTO QUESTION(QUESTION) VALUES (?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    const char *questionText = questionParam.question.c_str();
    size_t lengthQuestionText = strlen(questionText);
    rc = sqlite3_bind_text(stmt, 1, questionText, lengthQuestionText, NULL);
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

void QuestionDAO::updateQuestion(sqlite3 *conn, QuestionEntity questionParam)
{
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "UPDATE QUESTION SET QUESTION = ? WHERE ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "UPDATE prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    const char *questionText = questionParam.question.c_str();
    size_t lengthQuestionText = strlen(questionText);
    rc = sqlite3_bind_text(stmt, 1, questionText, lengthQuestionText, NULL);
    rc = sqlite3_bind_int(stmt, 2, questionParam.id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "UPDATE execute failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);
}

void QuestionDAO::deleteQuestion(sqlite3 *conn, QuestionEntity questionParam)
{
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "DELETE FROM QUESTION WHERE ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "DELETE prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, questionParam.id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "DELETE execute failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);
}

