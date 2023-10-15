#ifndef STUDYFILESTATUSDAO_H
#define STUDYFILESTATUSDAO_H

#include <iostream>
#include <vector>
#include <sqlite3.h>
#include "StudyFileStatusEntity.h"

using namespace std;

class StudyFileStatusDAO
{
    public:
        StudyFileStatusDAO();
        virtual ~StudyFileStatusDAO();

        vector<StudyFileStatusEntity> *getStudyFileStatus(sqlite3* conn);

    private:
        vector<StudyFileStatusEntity> studyFileStatus;
};

#endif // STUDYFILESTATUSDAO_H
