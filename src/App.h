#ifndef APP_H
#define APP_H

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "Database.h"
#include "Console.h"
#include "TopicCreator.h"
#include "TopicPicker.h"
#include "TopicCardCreator.h"
#include "TopicCardLoader.h"
#include "StudySession.h"

using namespace std;

class App {
public:
    App(string dbUrl);

private:
    sqlite3 *conn;
    string mainMenuOption;

    void mainLoop();
    void showMainMenu();
    void selectMainMenuOption();
    void doMenuOption();
};

#endif // APP_H
