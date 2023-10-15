#include <iostream>
#include <vector>
#include <sqlite3.h>
#include "StudyFileDAO.h"
#include "BoxEntity.h"
#include "TopicCardEntity.h"

using namespace std;

StudyFileDAO::StudyFileDAO()
{
    //ctor
}

StudyFileDAO::~StudyFileDAO()
{
    //dtor
}
void StudyFileDAO::addTopicCardToBox(sqlite3* conn, int topicCardId, int boxId)
{
   int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "INSERT INTO STUDY_FILE(TOPIC_CARD_ID, BOX_ID) VALUES (?, ?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, topicCardId);
    if (rc != SQLITE_OK)
    {
        cerr << "INSERT bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 2, boxId);
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

void StudyFileDAO::removeTopicCardFromBox(sqlite3* conn, int topicCardId, int boxId)
{
   int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "DELETE FROM STUDY_FILE WHERE TOPIC_CARD_ID = ? AND BOX_ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "DELETE prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, topicCardId);
    if (rc != SQLITE_OK)
    {
        cerr << "DELETE bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 2, boxId);
    if (rc != SQLITE_OK)
    {
        cerr << "DELETE bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "DELETE execute failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);
}

void StudyFileDAO::moveTopicCardFromBoxToBox(sqlite3* conn, int topicCardId, int fromBoxId, int toBoxId)
{
    removeTopicCardFromBox(conn, topicCardId, fromBoxId);
    addTopicCardToBox(conn, topicCardId, toBoxId);
}

BoxEntity StudyFileDAO::getBoxOfTheTopicCard(sqlite3* conn, int topicCardId)
{
    int rc;

    /* clean question */
    int boxId = 0;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, "SELECT BOX_ID FROM STUDY_FILE WHERE TOPIC_CARD_ID = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, topicCardId);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        boxId = sqlite3_column_int(stmt, 0);
    }
    else
    {
        cerr << "SELECT step failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    sqlite3_finalize(stmt);

    return BOXES[boxId];
}

vector<TopicCardEntity> *StudyFileDAO::getTopicCardsOfTheBox(sqlite3* conn, int boxId, int topicId)
{
    int rc;
    topicCards.clear();

    const char *sql =
        "select tc.ID, tc.TOPIC_ID, tc.CARD_ID from TOPIC_CARD tc "
        "inner join STUDY_FILE sf on sf.TOPIC_CARD_ID = tc.id "
        "where sf.BOX_ID = ? and tc.TOPIC_ID = ?;";

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, boxId);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter 1 failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 2, topicId);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter 2 failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    while (rc == SQLITE_ROW)
    {
        TopicCardEntity topicCard;
        topicCard.id = sqlite3_column_int(stmt, 0);
        topicCard.topicId = sqlite3_column_int(stmt, 1);
        topicCard.cardId = sqlite3_column_int(stmt, 2);

        topicCards.push_back(topicCard);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);

    return &topicCards;
}

vector<TopicEntity> *StudyFileDAO::getTopicsInBoxN(sqlite3 *conn, int boxId)
{
    int rc;
    topics.clear();

    const char *sql =
        "select distinct t.id, t.topic from study_file sf "
        "inner join topic_card tc on tc.id = sf.topic_card_id "
        "inner join topic t on t.id = tc.topic_id "
        "where sf.box_id = ?;";

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_bind_int(stmt, 1, boxId);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT bind parameter failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    while (rc == SQLITE_ROW)
    {
        TopicEntity topic;
        topic.id = sqlite3_column_int(stmt, 0);
        topic.topic = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));

        topics.push_back(topic);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);

    return &topics;
}
