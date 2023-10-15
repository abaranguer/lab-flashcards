#ifndef CARDDAO_H
#define CARDDAO_H

#include <sqlite3.h>
#include <vector>
#include "CardEntity.h"

class CardDAO
{
    public:
        CardDAO();
        virtual ~CardDAO();

        bool cardExists(sqlite3 *conn, int questionId, int answerId);
        void addCard(sqlite3 *conn, int questionId, int answerId);
        CardEntity *getLastInsertedCard(sqlite3 *conn);
        CardEntity *getCardById(sqlite3 *conn, int cardId);

    private:
        CardEntity card;
        vector<CardEntity> cards;
};

#endif // CARDDAO_H
