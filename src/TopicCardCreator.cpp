#include "TopicCardCreator.h"

TopicCardCreator::TopicCardCreator(sqlite3 *conn, int topicId)
{
    this->conn = conn;
    this->topicId = topicId;

    createTopicCards();
}

TopicCardCreator::~TopicCardCreator()
{
    //dtor
}

void TopicCardCreator::createTopicCards()
{
    showTitle();
    do
    {
        getQuestionAndAnswer();
        getNextAction();
        doAction();
    } while ((control == "1") || (control == "2"));
}

void TopicCardCreator::showTitle()
{
    cout << CLRSCR;
    cout << "    " << BOLD << "CREACIÓ DE FLASHCARDS" << RESET << endl;
}

void TopicCardCreator::getQuestionAndAnswer()
{
    cout << "\n\n" << BOLD << "Pregunta?\n\n" << RESET;
    cin.ignore();
    getline(cin, question);
    cout << "\n\n" << BOLD << "Resposta?\n\n" << RESET;
    getline(cin, answer);
}

void TopicCardCreator::getNextAction()
{
    do
    {
        cout << "\n(1) - Desar; (2) - Descartar; (3) - Tornar al menú; (4) - Desar i tornar al menú ";
        cin >> control;
    } while ((control != "1") && (control != "2") && (control != "3") && (control != "4"));
}

void TopicCardCreator::doAction()
{
    if ((control == "1") || (control == "4"))
    {
        save();
    }
}

void TopicCardCreator::save()
{
    addQuestion();
    addAnswer();
    addCard();
    addTopicCard();
}

void TopicCardCreator::addQuestion()
{
    QuestionDAO qdao;
    QuestionEntity q1;
    q1.question = question;
    qdao.addQuestion(conn, q1);
    QuestionEntity *q = qdao.getLastInsertedQuestion(conn);
    questionId = q->id;
}

void TopicCardCreator::addAnswer()
{
    AnswerDAO adao;
    AnswerEntity a1;
    a1.answer = answer;
    adao.addAnswer(conn, a1);
    AnswerEntity *a = adao.getLastInsertedAnswer(conn);
    answerId = a->id;
}

void TopicCardCreator::addCard()
{
    CardDAO cdao;
    cdao.addCard(conn, questionId, answerId);
    CardEntity *c = cdao.getLastInsertedCard(conn);
    cardId = c->id;
}

void TopicCardCreator::addTopicCard()
{
    TopicCardDAO tcdao;
    tcdao.addTopicCard(conn, topicId, cardId);
}
