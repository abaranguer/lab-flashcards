#ifndef STUDYFILEDAO_H
#define STUDYFILEDAO_H

#include <sqlite3.h>
#include <vector>
#include "TopicCardEntity.h"
#include "TopicEntity.h"
#include "BoxEntity.h"

class StudyFileDAO
{
    public:
        StudyFileDAO();
        virtual ~StudyFileDAO();
        void addTopicCardToBox(sqlite3 *conn, int topicCardId, int boxId);
        void removeTopicCardFromBox(sqlite3 *conn, int topicCardId, int boxId);
        void moveTopicCardFromBoxToBox(sqlite3 *conn, int topicCardId, int fromBoxId, int toBoxId);
        BoxEntity getBoxOfTheTopicCard(sqlite3 *conn, int topicCardId);
        vector<TopicCardEntity> *getTopicCardsOfTheBox(sqlite3 *conn, int boxId, int topicId);
        vector<TopicEntity> *getTopicsInBoxN(sqlite3 *conn, int boxId);

    private:
        vector<TopicCardEntity> topicCards;
        vector<TopicEntity> topics;
};

#endif // STUDYFILEDAO_H
