#include <iostream>
#include "CardDAO.h"

using namespace std;

CardDAO::CardDAO()
{
    //ctor
}

CardDAO::~CardDAO()
{
    //dtor
}

 void CardDAO::addCard(sqlite3 *conn, int questionId, int answerId)
 {
   int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "INSERT INTO CARD(QUESTION_ID, ANSWER_ID) VALUES (?, ?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, questionId);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 2, answerId);
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

bool CardDAO::cardExists(sqlite3* conn, int questionId, int answerId)
{
    bool retValue;
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID FROM CARD WHERE QUESTION_ID = ? and ANSWER_ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, questionId);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter 1 failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 2, answerId);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter 2 failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        retValue = true;
    }
    else
    {
        retValue = false;
    }

    sqlite3_finalize(stmt);

    return retValue;
}

CardEntity* CardDAO::getLastInsertedCard(sqlite3* conn)
{
    int rc;

    /* clean question */
    card.id = 0;
    card.questionId = 0;
    card.answerId = 0;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, QUESTION_ID, ANSWER_ID FROM CARD WHERE ID = (SELECT MAX(ID) FROM CARD);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        card.id = sqlite3_column_int(stmt, 0);
        card.questionId= sqlite3_column_int(stmt, 1);
        card.answerId= sqlite3_column_int(stmt, 2);
    }
    else
    {
        cerr << "SELECT step failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);

    return &card;
}

CardEntity  *CardDAO::getCardById(sqlite3* conn, int cardId)
{
     int rc;

    /* clean question */
    card.id = 0;
    card.questionId = 0;
    card.answerId = 0;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, QUESTION_ID, ANSWER_ID FROM CARD WHERE ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, cardId);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter  ailed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        card.id = sqlite3_column_int(stmt, 0);
        card.questionId= sqlite3_column_int(stmt, 1);
        card.answerId= sqlite3_column_int(stmt, 2);
    }
    else
    {
        cerr << "SELECT step failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);

    return &card;
}

