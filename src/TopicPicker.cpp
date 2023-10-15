#include "TopicPicker.h"

using namespace std;

TopicPicker::TopicPicker(sqlite3 *conn, string title)
{
    this->conn = conn;
    showTopics(title);
    selectTopic();
}

TopicPicker::~TopicPicker()
{
    //dtor
}

void TopicPicker::showTopics(string title)
{
    cout << CLRSCR;
    cout << "    " << BOLD << title << RESET << endl;
    cout << "\n\n" << BOLD << "Triar tòpic" << RESET << endl;

    TopicDAO tdao;
    topics = tdao.getAll(conn);

    int i;
    numTopics = topics->size();
    for(i = 0; i< numTopics; i++)
    {
        cout << "(" << (i + 1) << ") - " << topics->at(i).topic << endl;
    }
}

void TopicPicker::selectTopic(void)
{
    string option;

    do
    {
        cout << "\n(1 - " << numTopics << ") Triar Topic ";
        cin >> option;
    } while(!NumericMenuOptionsValidator::validate(numTopics, option));

    int opcioTriada = NumericMenuOptionsValidator::getNumericOption(option) - 1;

    TopicDAO tdao;
    topics = tdao.getAll(conn);
    cout << "\nOpcio triada: " << topics->at(opcioTriada).topic << endl;
    topicId = topics->at(opcioTriada).id;
}

int TopicPicker::getTopicId(void)
{
    return topicId;
}
