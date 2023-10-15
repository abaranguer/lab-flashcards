#ifndef QUESTIONDAO_H
#define QUESTIONDAO_H

#include <sqlite3.h>
#include "QuestionEntity.h"

using namespace std;

class QuestionDAO
{
    public:
        QuestionDAO();
        virtual ~QuestionDAO();

        QuestionEntity *getQuestionById(sqlite3 *conn, int id);
        bool existQuestionById(sqlite3 *conn, int id);
        void addQuestion(sqlite3 *conn, QuestionEntity question);
        void updateQuestion(sqlite3 *conn, QuestionEntity question);
        void deleteQuestion(sqlite3 *conn, QuestionEntity question);
        QuestionEntity *getLastInsertedQuestion(sqlite3 *conn);

    private:
        QuestionEntity question;
};

#endif // QUESTIONDAO_H
