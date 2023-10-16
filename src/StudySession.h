#ifndef STUDYSESSION_H
#define STUDYSESSION_H

#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>
#include "Console.h"
#include "StudyFileEntity.h"
#include "StudyFileStatusEntity.h"
#include "StudyFileStatusDAO.h"
#include "TopicBoxOption.h"
#include "Box.h"
#include "SessionRunner.h"

using namespace std;

class StudySession
{
    public:
		StudySession(void);
        StudySession(sqlite3 *conn);
        virtual ~StudySession();
        void showStudyFileInfo(sqlite3 *conn);

    private:
        vector<StudyFileStatusEntity> *studyFileStatus;
        vector<StudyFileEntity> *StudyFile;
        vector<TopicBoxOption> options;
        sqlite3 *conn;
        Box boxes[5];
        int boxSizes[5];

        void mainMenu(void);
        void backToMenu(string prompt);
        void showStudyFileStatus(void);
        void startSession(int boxIdChoosed, int topicIdChoosed);
        void loadStudyFile(int topicIdChoosed);

        bool validateNumOption(string opcio, int numOptions);
        bool isNumeric(string opcio);
        int toNumber(string opcio);

};

#endif // STUDYSESSION_H
