#ifndef RECOMMENDER_H
#define RECOMMENDER_H
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>
#include "StudyFileStatusEntity.h"
#include "StudyFileStatusDAO.h"
#include "TopicEntity.h"
#include "Console.h"
#include "BoxEntity.h"

using namespace std;

class Recommender
{
    public:
        Recommender(sqlite3 *conn, TopicEntity *topic);
        virtual ~Recommender();

    private:
        sqlite3 *conn;
        TopicEntity topic;
        vector<StudyFileStatusEntity> *studyFileStatus;

        void showStudyFileStatus(void);
        void infoBoxes(void);
        void suggestNextAction(int numCardsTopic);
        void suggestionsGenerator(void);
        bool lookForExcessOfCards(void);
        bool showSuggestIfExcessOfCards(int numCards, string topicName, int boxId);
        void showExcessBox(int numCards, int boxId);
        void lookForBoxWithCards(void);
        void infoBox(string topic, int numCards, int boxId);
        void noMoreCards(void);
};

#endif // RECOMMENDER_H
