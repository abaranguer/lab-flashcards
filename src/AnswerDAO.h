#ifndef ANSWERDAO_H
#define ANSWERDAO_H

#include <sqlite3.h>
#include "AnswerEntity.h"

using namespace std;

class AnswerDAO
{
    public:
        AnswerDAO();
        virtual ~AnswerDAO();
        AnswerEntity *getAnswerById(sqlite3 *conn, int id);
        bool existAnswerById(sqlite3 *conn, int id);
        void addAnswer(sqlite3 *conn, AnswerEntity answer);
        void updateAnswer(sqlite3 *conn, AnswerEntity answer);
        void deleteAnswer(sqlite3 *conn, AnswerEntity answer);
        AnswerEntity *getLastInsertedAnswer(sqlite3 *conn);

    private:
        AnswerEntity answer;
};

#endif // ANSWERDAO_H
