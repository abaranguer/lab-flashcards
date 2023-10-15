#ifndef TOPICCARDLOADER_H
#define TOPICCARDLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "Console.h"
#include "TopicCardDAO.h"
#include "StudyFileDAO.h"

using namespace std;

class TopicCardLoader
{
    public:
        TopicCardLoader(sqlite3 *conn, int topicId);
        virtual ~TopicCardLoader();

    private:
        sqlite3 *conn;
        int topicId;
        void loadTopicCards(void);
        void moveNPendingCardsToBoxOne(int roomAvailable);
        int minNumCards(int roomAvailable, int numPendingCards);
        void backToMenu(string prompt);
};

#endif // TOPICCARDLOADER_H
