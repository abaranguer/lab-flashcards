#include <iostream>
#include "TopicCardDAO.h"

using namespace std;

TopicCardDAO::TopicCardDAO()
{
    //ctor
}

TopicCardDAO::~TopicCardDAO()
{
    //dtor
}

bool TopicCardDAO::topicCardExists(sqlite3* conn, int topicId, int cardId)
{
    bool retValue;
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID FROM TOPIC_CARD WHERE TOPIC_ID = ? AND CARD_ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, topicId);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter 1 failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 2, cardId);
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

void TopicCardDAO::addTopicCard(sqlite3* conn, int topicId, int cardId)
{
   int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "INSERT INTO TOPIC_CARD(TOPIC_ID, CARD_ID) VALUES (?, ?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, topicId);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 2, cardId);
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

TopicCardEntity* TopicCardDAO::getLastInsertedTopicCard(sqlite3* conn)
{
    int rc;

    /* clean question */
    topicCard.id = 0;
    topicCard.topicId = 0;
    topicCard.cardId = 0;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, TOPIC_ID, CARD_ID FROM TOPIC_CARD WHERE ID = (SELECT MAX(ID) FROM TOPIC_CARD);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        topicCard.id = sqlite3_column_int(stmt, 0);
        topicCard.topicId = sqlite3_column_int(stmt, 1);
        topicCard.cardId = sqlite3_column_int(stmt, 2);
    }
    else
    {
        cerr << "SELECT step failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);

    return &topicCard;
}


vector<TopicCardEntity> *TopicCardDAO::getPendingTopicCardByTopicId(sqlite3 *conn, int topicId)
{
    int rc;

    topicCards.clear();

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, TOPIC_ID, CARD_ID FROM TOPIC_CARD WHERE TOPIC_ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, topicId);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    while (rc == SQLITE_ROW)
    {
        TopicCardEntity tce;
        tce.id = sqlite3_column_int(stmt, 0);
        tce.topicId = sqlite3_column_int(stmt, 1);
        tce.cardId = sqlite3_column_int(stmt, 2);

        topicCards.push_back(tce);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);

    return &topicCards;
}
