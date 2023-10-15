#ifndef TOPICCARDDAO_H
#define TOPICCARDDAO_H

#include <sqlite3.h>
#include <vector>
#include "TopicCardEntity.h"

class TopicCardDAO
{
    public:
        TopicCardDAO();
        virtual ~TopicCardDAO();

        bool topicCardExists(sqlite3 *conn, int topicId, int cardId);
        void addTopicCard(sqlite3 *conn, int topicId, int cardId);
        TopicCardEntity *getLastInsertedTopicCard(sqlite3 *conn);
        vector<TopicCardEntity> *getPendingTopicCardByTopicId(sqlite3 *conn, int topicId);

    private:
        TopicCardEntity topicCard;
        vector<TopicCardEntity> topicCards;
};

#endif // TOPICCARDDAO_H
