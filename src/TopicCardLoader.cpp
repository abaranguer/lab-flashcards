#include "TopicCardLoader.h"

TopicCardLoader::TopicCardLoader(sqlite3 *conn, int topicId)
{
    this->conn = conn;
    this->topicId = topicId;

    loadTopicCards();
}

TopicCardLoader::~TopicCardLoader()
{
    //dtor
}

void TopicCardLoader::loadTopicCards()
{
    TopicCardDAO tcdao;
    int numCards;
    vector<TopicCardEntity> *topicCards;

    topicCards = tcdao.getPendingTopicCardByTopicId(conn, topicId);
    int pendingCards = topicCards->size();
    cout << "\nHi han " << pendingCards << " targetes pendents" << endl;

    StudyFileDAO sfdao;
    topicCards = sfdao.getTopicCardsOfTheBox(conn, BOX_1_ID, topicId);
    int cardsInBoxOne = topicCards->size();
    int roomAvailable = 20 - cardsInBoxOne;
    cout << "Hi han " << cardsInBoxOne << " a la primera caixa." << endl;
    if (roomAvailable > 0)
    {
        cout << "Hi ha espai per a " << roomAvailable << " noves targetes." << endl;
        numCards = minNumCards(roomAvailable, pendingCards);
        cout << "Es mouen " << numCards << " targetes a la primera caixa." << endl;
        moveNPendingCardsToBoxOne(roomAvailable);
        topicCards = sfdao.getTopicCardsOfTheBox(conn, BOX_1_ID, topicId);
        cardsInBoxOne = topicCards->size();
        cout << "Ara hi han " << cardsInBoxOne << " targetes a la primera caixa.\n" << endl;
    }
    else
    {
        cout << "No hi ha espai per a noves targetes a la primera caixa.\n" << endl;
    }

    backToMenu("Tornar al menú principal.");
}

void TopicCardLoader::moveNPendingCardsToBoxOne(int roomAvailable)
{
    TopicCardDAO tcdao;
    StudyFileDAO sfdao;

    vector<TopicCardEntity> *topicCards;
    topicCards = tcdao.getPendingTopicCardByTopicId(conn, topicId);
    int numPendingCards = topicCards->size();
    int numCards;

    numCards = minNumCards(roomAvailable, numPendingCards);

    int i;
    for(i=0; i<numCards; i++)
    {
        int topicCardId = topicCards->at(i).id;
        sfdao.moveTopicCardFromBoxToBox(conn, topicCardId, BOX_PENDING_ID, BOX_1_ID);
    }
}

int TopicCardLoader::minNumCards(int roomAvailable, int numPendingCards)
{
    int numCards;

    if (numPendingCards >= roomAvailable)
    {
        numCards = roomAvailable;
    }
    else
    {
        numCards = numPendingCards;
    }

    return numCards;
}

void TopicCardLoader::backToMenu(string prompt)
{
    string dummy;
    do
    {
        cout << "(0) - " << prompt << endl;
        cin >> dummy;
    } while (dummy != "0");
}
