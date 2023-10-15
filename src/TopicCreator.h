#ifndef TOPICCREATOR_H
#define TOPICCREATOR_H

#include <iostream>
#include <sqlite3.h>
#include "Console.h"
#include <string>
#include "TopicDAO.h"
#include "TopicEntity.h"

using namespace std;

class TopicCreator
{
    public:
        TopicCreator(sqlite3 *conn);
        virtual ~TopicCreator();
        TopicEntity getTopic(void);
        string getTopicName(void);
        int getTopicId(void);

    private:
        sqlite3 *conn;
        TopicEntity topic;

        void createTopic(void);
        void setTopic(void);
        void addTopic(void);
};

#endif // TOPICCREATOR_H
