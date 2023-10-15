#ifndef SESSIONRUNNER_H
#define SESSIONRUNNER_H

#include <iostream>
#include <sqlite3.h>
#include "Console.h"
#include "Card.h"
#include "QuestionEntity.h"
#include "AnswerEntity.h"
#include "TopicCardEntity.h"
#include "CardEntity.h"
#include "StudyFileEntity.h"
#include "CardDAO.h"
#include "TopicDAO.h"
#include "QuestionDAO.h"
#include "AnswerDAO.h"
#include "StudyFileDAO.h"
#include "Recommender.h"

using namespace std;

class SessionRunner
{
    public:
        SessionRunner(sqlite3 *conn, int boxIdChoosed, int topicIdChoosed);

    private:
        sqlite3 *conn;
        bool follow;
        int currentBoxId;
        int topicId;
        TopicEntity topic;
        TopicCardEntity currentTopicCard;
        StudyFileEntity currentStudyFileCard;
        vector<TopicCardEntity> studyFile[7];

        void runSession(void);
        void moveCardRightAnswer(void);
        void moveCardWrongAnswer(void);
        void loadStudyFile(int topicIdChoosed);
        void showStudyFileStatus(void);
        string getQuestion(void);
        string getAnswer(void);
        void waitFor0KeyPressed(string prompt);
        bool canContinue(void);
        void loadStudyFileBox(vector<TopicCardEntity> *sf, int boxId);
        void suggestNewActions(void);
        string showQuestionAnswer(void);
};

#endif // SESSIONRUNNER_H
