#include "Recommender.h"

using namespace std;

Recommender::Recommender(sqlite3 *conn, TopicEntity *topic)
{
    this->conn = conn;
    this->topic.id = topic->id;
    this->topic.topic = topic->topic;

    showStudyFileStatus();
}

Recommender::~Recommender()
{
    //dtor
}

void Recommender::showStudyFileStatus(void)
{
    cout << "\n\n" << BOLD << "Estat actual del fitxer d'estudi" << RESET << endl;

    infoBoxes();
}

void Recommender::infoBoxes(void)
{
    StudyFileStatusDAO sfsdao;
    studyFileStatus = sfsdao.getStudyFileStatus(conn);
    int numElems = studyFileStatus->size();
    int numCardsTopic = 0;
    int numCards = 0;
    int topicId;
    string topicName;
    int boxId;
    int i;
    for(i = 0; i < numElems; i++)
    {
        if ((studyFileStatus->at(i).boxId != 0)
        && (studyFileStatus->at(i).boxId != 6))
        {
            numCards = studyFileStatus->at(i).numCards;
            topicId =  studyFileStatus->at(i).topicId;
            topicName = studyFileStatus->at(i).topic;
            boxId = studyFileStatus->at(i).boxId;
            infoBox(topicName, numCards, boxId);
            if (topicId == topic.id)
            {
                numCardsTopic = numCardsTopic + numCards;
            }
        }
    }

    suggestNextAction(numCardsTopic);
}

void Recommender::suggestNextAction(int numCardsTopic)
{
    if (numCardsTopic == 0)
    {
        noMoreCards();
    }
    else
    {
        suggestionsGenerator();
    }
}

void Recommender::suggestionsGenerator(void)
{
    if (!lookForExcessOfCards())
    {
        lookForBoxWithCards();
    }
}

bool Recommender::lookForExcessOfCards()
{
    bool foundExcess = false;
    StudyFileStatusDAO sfsdao;
    studyFileStatus = sfsdao.getStudyFileStatus(conn);
    int numElems = studyFileStatus->size();
    int numCards = 0;
    int topicId;
    string topicName;
    int boxId;
    int i;
    for(i = 0; i < numElems; i++)
    {
        if ((studyFileStatus->at(i).boxId != 0)
        && (studyFileStatus->at(i).boxId != 6))
        {
            numCards = studyFileStatus->at(i).numCards;
            topicId =  studyFileStatus->at(i).topicId;
            topicName = studyFileStatus->at(i).topic;
            boxId = studyFileStatus->at(i).boxId;
            if (topicId == topic.id)
            {
                foundExcess = showSuggestIfExcessOfCards(numCards, topicName, boxId);
            }
        }
    }

    return foundExcess;
}

bool Recommender::showSuggestIfExcessOfCards(
    int numCards,
    string topicName,
    int boxId)
{
    bool foundExcess = false;

    if ((boxId == BOX_1_ID) && (numCards > 20))
    {
        foundExcess = true;
        showExcessBox(numCards, BOX_1_ID);
    }

    if ( (!foundExcess) && (boxId == BOX_2_ID) && (numCards > 40))
    {
        foundExcess = true;
        showExcessBox(numCards, BOX_2_ID);
    }

    if ( (!foundExcess) && (boxId == BOX_3_ID) && (numCards > 60))
    {
        foundExcess = true;
        showExcessBox(numCards, BOX_3_ID);
    }

    if ( (!foundExcess) && (boxId == BOX_4_ID) && (numCards > 140))
    {
        foundExcess = true;
        showExcessBox(numCards, BOX_4_ID);
    }

    if ( (!foundExcess) && (boxId == BOX_5_ID) && (numCards > 300))
    {
        foundExcess = true;
        showExcessBox(numCards, BOX_5_ID);
    }

    return foundExcess;}

void Recommender::showExcessBox(int numCards, int boxId)
{
    string beginText = "Es recomana seguir amb la caixa ";
    string middleText = " perquè té un excés (";
    string endText = ") de targetes.";

    cout << "\n\n" << beginText << BOLD << boxId << RESET
        << middleText << numCards << endText << endl;
}

void Recommender::lookForBoxWithCards()
{
    StudyFileStatusDAO sfsdao;
    studyFileStatus = sfsdao.getStudyFileStatus(conn);
    int numElems = studyFileStatus->size();
    int topicId;
    string topicName;
    int boxId;
    int i;
    for(i = 0; i < numElems; i++)
    {
        if ((studyFileStatus->at(i).boxId != 0)
        && (studyFileStatus->at(i).boxId != 6))
        {
            topicId =  studyFileStatus->at(i).topicId;
            topicName = studyFileStatus->at(i).topic;
            boxId = studyFileStatus->at(i).boxId;
            if (topicId == topic.id)
            {
                cout << "\n\nEs recomana seguir amb la caixa "
                    << boxId << endl;
                break;
            }
        }
    }
}

void Recommender::infoBox(string topicName, int numCards, int boxId)
{
    if (topic.topic == topicName)
    {
        if (numCards > 1)
        {
            cout    << "A la caixa " << boxId
                    << " hi han " << numCards << " targetes del topic '"
                    << topicName << "'" << endl;
        } else
        {
            cout    << "A la caixa " << boxId
                    << " hi ha " << numCards << " targeta del topic '"
                    << topicName << "'" << endl;
        }
    }
}

void Recommender::noMoreCards(void)
{
    cout << "\n" << BOLD << "No hi han targetes del tòpic '"
        << topic.topic << "' al fitxer d'estudi!" << RESET << endl;
    cout << "- Podeu carregar més targetes per al tòpic." << endl;
    cout << "- O bé podeu triar un tòpic diferent." << endl;
    cout << "\n\n" << endl;
}
