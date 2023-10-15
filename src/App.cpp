#include "App.h"

using namespace std;

App::App(string dbUrl)
{
    Database database(dbUrl);
    conn = database.getConn();
    mainLoop();
}

void App::mainLoop()
{
    while(true)
    {
        showMainMenu();
        selectMainMenuOption();
        doMenuOption();
    }
}

void App::showMainMenu()
{
    cout << CLRSCR;
    cout << "    " << BOLD << "FITXER D'ESTUDI (Mètode Leitner)" << RESET << endl;
    cout << "\n\n" << BOLD << "(1) Crear Topic." << RESET << endl;
    cout << BOLD << "(2) Crear targetes." << RESET << endl;
    cout << BOLD << "(3) Carregar targetes al fitxer d'estudi." << RESET << endl;
    cout << BOLD << "(4) Sessió d'estudi." << RESET << endl;
    cout << BOLD << "(5) Sortir." << RESET << endl;
}

void App::selectMainMenuOption()
{
    do
    {
        cout << "\n(1 - 5) ";
        cin >> mainMenuOption;
    } while ((mainMenuOption != "1") && (mainMenuOption != "2") &&
             (mainMenuOption != "3") && (mainMenuOption != "4") &&
             (mainMenuOption != "5"));
}

void App::doMenuOption()
{
    int topicId;

    if (mainMenuOption == "1")
    {
        TopicCreator topicCreator(conn);
    }

    if (mainMenuOption == "2")
    {
        TopicPicker topicPicker(conn, "CREACIÓ DE TARGETES");
        topicId = topicPicker.getTopicId();
        TopicCardCreator topicCardCreator(conn, topicId);
    }

    if (mainMenuOption == "3")
    {
        TopicPicker topicPicker(conn, "CÀRREGA DE TARGETES AL FITXER D'ESTUDI");
        topicId = topicPicker.getTopicId();
        TopicCardLoader topicCardLoader(conn, topicId);
    }

    if (mainMenuOption == "4")
    {
        StudySession ss(conn);
    }

    if (mainMenuOption == "5")
    {
        cout << CLRSCR;
        cout << "Passi-ho bé i fins a la propera." << endl;
        exit(0);
    }
}
