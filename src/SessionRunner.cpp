#include "SessionRunner.h"

using namespace std;

SessionRunner::SessionRunner(sqlite3 *conn, int boxIdChoosed, int topicIdChoosed)
{
    this->conn = conn;
    this->currentBoxId = boxIdChoosed;
    this->topicId = topicIdChoosed;

    loadStudyFile(topicIdChoosed);
    TopicDAO tdao;
    TopicEntity *topicAux;
    topicAux = tdao.getTopicById(conn, topicIdChoosed);
    topic.id = topicAux->id;
    topic.topic = topicAux->topic;
    runSession();
}

void SessionRunner::runSession(void)
{
    follow = true;
    string prompt;

    while (follow) {
        TopicCardEntity tce = studyFile[currentBoxId].at(0);
        currentTopicCard.id = tce.id;
        currentTopicCard.cardId = tce.cardId;
        currentTopicCard.topicId = tce.topicId;

        prompt = showQuestionAnswer();

        if (prompt == "1")
        {
            moveCardRightAnswer();
        } else {
            moveCardWrongAnswer();
        }

        do {
            cout << "    (C) Continuar? ; (S) Sortir" << endl;
            cin >> prompt;
        } while ((prompt != "c") && (prompt != "C") && (prompt != "s") && (prompt != "S"));

        if ((prompt == "s") || (prompt == "S"))
        {
            follow = false;
        }

        if (!canContinue())
        {
            follow = false;
        }
    }
}

string SessionRunner::showQuestionAnswer()
{
    string question;
    string answer;

    question = getQuestion();
    answer = getAnswer();

    string prompt;

    cout << CLRSCR;
    cout << BOLD << "    SESSIÓ D'ESTUDI (TÒPIC: '" << topic.topic << "')" << RESET << endl;
    cout << "\n\n    " << BOLD << "Pregunta: " << RESET << endl;
    cout << "\n" << question << "\n" << endl;
    waitFor0KeyPressed("Mostrar resposta.");
    cout << "    " << BOLD << "Resposta: " << RESET << endl;
    cout << "\n" << answer << "\n" << endl;
    do {
        cout << "    (1) Correcte ; (2) Incorrecte; " << endl;
        cin >> prompt;
    } while ((prompt != "1") && (prompt != "2"));

    return prompt;
}

void SessionRunner::moveCardRightAnswer(void)
{
    int nextBoxId = currentBoxId + 1;
    studyFile[currentBoxId].erase(studyFile[currentBoxId].begin());
    studyFile[nextBoxId].push_back(currentTopicCard);
    StudyFileDAO sfdao;
    sfdao.moveTopicCardFromBoxToBox(conn, currentTopicCard.id, currentBoxId, nextBoxId);
}

void SessionRunner::moveCardWrongAnswer(void)
{
    studyFile[currentBoxId].erase(studyFile[currentBoxId].begin());
    studyFile[BOX_1_ID].push_back(currentTopicCard);
    StudyFileDAO sfdao;
    sfdao.moveTopicCardFromBoxToBox(conn, currentTopicCard.id, currentBoxId, BOX_1_ID);
}

void SessionRunner::loadStudyFile(int topicIdChoosed)
{
    StudyFileDAO sfdao;
    vector<TopicCardEntity> *sf;

    sf = sfdao.getTopicCardsOfTheBox(conn, BOX_PENDING_ID, topicId);
    loadStudyFileBox(sf, BOX_PENDING_ID);
    sf = sfdao.getTopicCardsOfTheBox(conn, BOX_1_ID, topicId);
    loadStudyFileBox(sf, BOX_1_ID);
    sf = sfdao.getTopicCardsOfTheBox(conn, BOX_2_ID, topicId);
    loadStudyFileBox(sf, BOX_2_ID);
    sf = sfdao.getTopicCardsOfTheBox(conn, BOX_3_ID, topicId);
    loadStudyFileBox(sf, BOX_3_ID);
    sf = sfdao.getTopicCardsOfTheBox(conn, BOX_4_ID, topicId);
    loadStudyFileBox(sf, BOX_4_ID);
    sf = sfdao.getTopicCardsOfTheBox(conn, BOX_5_ID, topicId);
    loadStudyFileBox(sf, BOX_5_ID);
    sf = sfdao.getTopicCardsOfTheBox(conn, BOX_LEARNED_CARDS_ID, topicId);
    loadStudyFileBox(sf, BOX_LEARNED_CARDS_ID);
}

string SessionRunner::getQuestion(void)
{
    CardDAO cdao;
    QuestionDAO qdao;
    CardEntity *auxCard;
    QuestionEntity *auxQuestion;
    auxCard = cdao.getCardById(conn, currentTopicCard.cardId);
    auxQuestion = qdao.getQuestionById(conn, auxCard->questionId);

    return auxQuestion->question;
}

string SessionRunner::getAnswer(void)
{
    CardDAO cdao;
    AnswerDAO adao;
    CardEntity *auxCard;
    AnswerEntity *auxAnswer;
    auxCard = cdao.getCardById(conn, currentTopicCard.cardId);
    auxAnswer = adao.getAnswerById(conn, auxCard->answerId);

    return auxAnswer->answer;
}

void SessionRunner::waitFor0KeyPressed(string prompt)
{
    string dummy;
    do
    {
        cout << "(0) - " << prompt << endl;
        cin >> dummy;
    } while (dummy != "0");
}

void SessionRunner::loadStudyFileBox(vector<TopicCardEntity> *sf, int boxId)
{
    studyFile[boxId].clear();
    int numCards = sf->size();
    for(int i=0; i < numCards; i++)
    {
        TopicCardEntity tce;
        tce.id = sf->at(i).id;
        tce.topicId = sf->at(i).topicId;
        tce.cardId = sf->at(i).cardId;
        studyFile[boxId].push_back(tce);
    }
}

bool SessionRunner::canContinue(void)
{
    bool retValue;

    if (studyFile[currentBoxId].size() == 0)
    {
        cout << BOLD << "\n\nNo hi han més targetes del tòpic '"
            << topic.topic << "' a la caixa " << currentBoxId
            << endl;
        suggestNewActions();
        retValue = false;
    }
    else
        retValue = true;

    return retValue;
}

void SessionRunner::suggestNewActions()
{
    Recommender recommender(conn, &topic);
}
