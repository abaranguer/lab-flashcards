#ifndef BOXDAO_H
#define BOXDAO_H

#include <sqlite3.h>
#include <vector>
#include "BoxEntity.h"

using namespace std;

class BoxDAO
{
public:
    BoxDAO();
    virtual ~BoxDAO();
    vector<BoxEntity> *getAll(sqlite3 *conn);

private:
    vector<BoxEntity> boxes;
};

#endif // BOXDAO_H
