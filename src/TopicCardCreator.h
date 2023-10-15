#ifndef TOPICCARDCREATOR_H
#define TOPICCARDCREATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "Console.h"
#include "TopicDAO.h"
#include "QuestionDAO.h"
#include "AnswerDAO.h"
#include "CardDAO.h"
#include "TopicCardDAO.h"

using namespace std;

class TopicCardCreator
{
    public:
        TopicCardCreator(sqlite3 *conn, int topicId);
        virtual ~TopicCardCreator();

    private:
        sqlite3 *conn;
        string question;
        string answer;
        string control;
        int topicId;
        int cardId;
        int questionId;
        int answerId;

        void createTopicCards();
        void showTitle();
        void getQuestionAndAnswer();
        void getNextAction();
        void doAction();
        void save();
        void addQuestion();
        void addAnswer();
        void addCard();
        void addTopicCard();
};

#endif // TOPICCARDCREATOR_H
