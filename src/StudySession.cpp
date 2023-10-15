#include "StudySession.h"

using namespace std;

StudySession::StudySession(sqlite3* conn)
{
    int sizes[] = {20, 40, 60, 140, 300};

    for(int i = 0; i < 5; i++)
    {
        Box box(BOXES[i], sizes[i]);
        boxes[i] = box;
    }

    this->conn = conn;

    mainMenu();
}

StudySession::~StudySession()
{
    //dtor
}

void StudySession::mainMenu()
{
    showStudyFileStatus();

    backToMenu("Torna al menú principal");
}

void StudySession::backToMenu(string prompt)
{
    string dummy;
    do
    {
        cout << "(0) - " << prompt << endl;
        cin >> dummy;
    } while (dummy != "0");
}

void StudySession::showStudyFileStatus()
{
    options.clear();

    cout << CLRSCR;
    cout << "    " << BOLD << "SESSIÓ d'ESTUDI" << RESET << endl;
    cout << "\n\n" << BOLD << "Estat actual del fitxer d'estudi" << RESET << endl;

    StudyFileStatusDAO sfsdao;
    studyFileStatus = sfsdao.getStudyFileStatus(conn);
    int numElems = studyFileStatus->size();

    int numCards = 0;
    string topic;
    int boxId;

    int boxIdChoosed;
    int topicIdChoosed;

    int i;
    int numOptions = 0;
    bool hasOne = false;
    for(i = 0; i < numElems; i++)
    {
        if ((studyFileStatus->at(i).boxId != 0) && (studyFileStatus->at(i).boxId != 6))
        {
            hasOne = true;
            numOptions++;
            numCards = studyFileStatus->at(i).numCards;
            topic = studyFileStatus->at(i).topic;
            boxId = studyFileStatus->at(i).boxId;
            if (numCards > 1)
            {
                cout    << "(" << numOptions << ") - A la caixa " << boxId
                        << " hi han " << numCards << " targetes del topic '"
                        << topic << "'" << endl;
            } else {
                cout    << "(" << numOptions << ") - A la caixa " << boxId
                        << " hi ha " << numCards << " targeta del topic '"
                        << topic << "'" << endl;
            }
            TopicBoxOption opt;
            opt.topicId = studyFileStatus->at(i).topicId;
            opt.topic = topic;
            opt.boxId = boxId;

            options.push_back(opt);
        }    }

    if (hasOne)
    {
    	numOptions++;
        cout    << "\n(" << numOptions << ") - Tornar al menú anterior." << endl;
		string option;
		do
		{
			cout << "\n(1 - " << numOptions << ") Triar caixa inicial i Topic " << endl;
			cin >> option;
		} while(!validateNumOption(option, numOptions));

		int index = toNumber(option);
		if (index != numOptions)
		{
			index = index - 1;
			boxIdChoosed = options.at(index).boxId;
			topicIdChoosed = options.at(index).topicId;
			cout    << "\nSeleccionada caixa " << boxIdChoosed
					<< " i topic '" << options.at(index).topic << "'" << endl;

			startSession(boxIdChoosed, topicIdChoosed);
		}
    }
    else
    {
        cout << "\nNO HI HAN TARGETES AL FITXER d'ESTUDI" << endl;
    }
}

bool StudySession::validateNumOption(string opcio, int numOptions)
{
    bool retValue = false;
    if (isNumeric(opcio))
    {
        int numericOption = toNumber(opcio);

        if ((numericOption >= 1) && (numericOption <= numOptions))
        {
            retValue = true;
        }
    }

    return retValue;
}

bool StudySession::isNumeric(string opcio)
{
    string::const_iterator it = opcio.begin();

    while (it != opcio.end() && isdigit(*it)) ++it;

    return !opcio.empty() && (it == opcio.end());
}

int StudySession::toNumber(string opcio)
{
    int numOpcio = stoi(opcio);

    return numOpcio;
}

void StudySession::startSession(int boxIdChoosed, int topicIdChoosed)
{
    SessionRunner sessionRunner(conn, boxIdChoosed, topicIdChoosed);
}

