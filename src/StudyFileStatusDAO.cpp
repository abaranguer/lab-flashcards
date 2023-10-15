#include "StudyFileStatusDAO.h"

using namespace std;

StudyFileStatusDAO::StudyFileStatusDAO()
{
    //ctor
}

StudyFileStatusDAO::~StudyFileStatusDAO()
{
    //dtor
}
vector<StudyFileStatusEntity> *StudyFileStatusDAO::getStudyFileStatus(sqlite3* conn)
{
    int rc;
    studyFileStatus.clear();

    const char *sql =
        "select NUM_CARDS, TOPIC_ID, TOPIC, BOX_ID from STUDY_FILE_STATUS;";

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(conn, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "SELECT prepare statement failed: " << sqlite3_errmsg(conn) << endl;
        exit(0);
    }

    rc = sqlite3_step(stmt);
    while (rc == SQLITE_ROW)
    {
        StudyFileStatusEntity sfse;
        sfse.numCards = sqlite3_column_int(stmt, 0);
        sfse.topicId = sqlite3_column_int(stmt, 1);
        sfse.topic = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        sfse.boxId = sqlite3_column_int(stmt, 3);

        studyFileStatus.push_back(sfse);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);

    return &studyFileStatus;
}
