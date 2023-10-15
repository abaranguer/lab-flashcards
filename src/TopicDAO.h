#ifndef TOPICDAO_H
#define TOPICDAO_H
#include <sqlite3.h>
#include <vector>
#include "TopicEntity.h"

using namespace std;

class TopicDAO
{
public:
    TopicDAO();
    virtual ~TopicDAO();
    TopicEntity *getTopicById(sqlite3 *conn, int id);
    bool existTopicById(sqlite3 *conn, int id);
    void addTopic(sqlite3 *conn, TopicEntity topic);
    void updateTopic(sqlite3 *conn, TopicEntity topic);
    void deleteTopic(sqlite3 *conn, TopicEntity topic);
    TopicEntity *getLastInsertedTopic(sqlite3 *conn);
    vector<TopicEntity> *getAll(sqlite3 *conn);

private:
    TopicEntity topic;
    vector<TopicEntity> topics;
};

#endif // TOPICDAO_H
