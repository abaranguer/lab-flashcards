#include <iostream>
#include <string>
#include <cstring>
#include <sqlite3.h>
#include "TopicDAO.h"
#include "TopicEntity.h"

using namespace std;

TopicDAO::TopicDAO()
{
    // TODO ctor
}

TopicDAO::~TopicDAO()
{
    // TODO dtor
}

bool TopicDAO::existTopicById(sqlite3 *conn, int id)
{
    int rc;
    int numOfRows = 0;
    bool retValue = false;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT COUNT(*) FROM TOPIC WHERE ID = ?;", -1, &stmt, NULL);
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

TopicEntity* TopicDAO::getTopicById(sqlite3 *conn, int id)
{
    int rc;

    /* clean topic */
    topic.id = 0;
    topic.topic = "";

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, TOPIC FROM TOPIC WHERE ID = ?;", -1, &stmt, NULL);
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
        topic.id = sqlite3_column_int(stmt, 0);
        topic.topic = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    }
    else
    {
        cerr << "SELECT no data found: " << sqlite3_errmsg(conn) << endl;
        topic.id = -1;
        topic.topic = "";
    }

    sqlite3_finalize(stmt);

    return &topic;
}

TopicEntity *TopicDAO::getLastInsertedTopic(sqlite3 *conn)
{
    int rc;

    /* clean topic */
    topic.id = 0;
    topic.topic = "";

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, TOPIC FROM TOPIC WHERE ID = (SELECT MAX(ID) FROM TOPIC);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        topic.id = sqlite3_column_int(stmt, 0);
        topic.topic = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    }
    else
    {
        cerr << "SELECT step failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);

    return &topic;
}

void TopicDAO::addTopic(sqlite3 *conn, TopicEntity topicParam)
{
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "INSERT INTO TOPIC(TOPIC) VALUES (?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    const char *topicText = topicParam.topic.c_str();
    size_t lengthTopicText = strlen(topicText);
    rc = sqlite3_bind_text(stmt, 1, topicText, lengthTopicText, NULL);
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

void TopicDAO::updateTopic(sqlite3 *conn, TopicEntity topicParam)
{
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "UPDATE TOPIC SET TOPIC = ? WHERE ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "UPDATE prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    const char *topicText = topicParam.topic.c_str();
    size_t lengthTopicText = strlen(topicText);
    rc = sqlite3_bind_text(stmt, 1, topicText, lengthTopicText, NULL);
    rc = sqlite3_bind_int(stmt, 2, topicParam.id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "UPDATE execute failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);
}

void TopicDAO::deleteTopic(sqlite3 *conn, TopicEntity topicParam)
{
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "DELETE FROM TOPIC WHERE ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "DELETE prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, topicParam.id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "DELETE execute failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);
}

vector<TopicEntity> *TopicDAO::getAll(sqlite3 *conn)
{
    int rc;

    /* clean list */
    topics.clear();

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT ID, TOPIC FROM TOPIC ORDER BY ID;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        TopicEntity topicAux;
        topicAux.id = sqlite3_column_int(stmt, 0);
        topicAux.topic = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));

        topics.push_back(topicAux);
    }

    if (rc != SQLITE_DONE)
    {
        cerr << "SELECT failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);

    return &topics;
}
