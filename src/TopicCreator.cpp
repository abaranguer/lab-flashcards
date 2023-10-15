#include "TopicCreator.h"

TopicCreator::TopicCreator(sqlite3 *conn)
{
    this->conn = conn;
    createTopic();
}

TopicCreator::~TopicCreator()
{
    //dtor
}

void TopicCreator::createTopic()
{
    setTopic();
    addTopic();
}

void TopicCreator::setTopic()
{
    string topicName;
    cout << CLRSCR;
    cout << "    " << BOLD << "CREACIÓ de TÒPIC" << RESET << endl;
    cout << "\n\n" << BOLD << "Tòpic? " << RESET;
    cin.ignore();
    getline(cin, topicName);
    topic.topic = topicName;
}

void TopicCreator::addTopic()
{
    TopicDAO tdao;
    tdao.addTopic(conn, topic);
    TopicEntity *te = tdao.getLastInsertedTopic(conn);
    topic.id = te->id;
}

TopicEntity TopicCreator::getTopic()
{
    return topic;}

int TopicCreator::getTopicId()
{
    return topic.id;
}

string TopicCreator::getTopicName()
{
    return topic.topic;
}
