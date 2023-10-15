#ifndef TOPICPICKER_H
#define TOPICPICKER_H

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "Database.h"
#include "Console.h"
#include "TopicEntity.h"
#include "TopicDAO.h"
#include "NumericMenuOptionsValidator.h"

using namespace std;

class TopicPicker
{
    public:
        TopicPicker(sqlite3 *conn, string title);
        virtual ~TopicPicker();
        int getTopicId();

    private:
        sqlite3 *conn;
        vector<TopicEntity> *topics;
        int topicId;
        int numTopics;

        void showTopics(string title);
        void selectTopic(void);
};

#endif // TOPICPICKER_H
