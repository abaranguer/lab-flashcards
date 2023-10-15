#ifndef BOXENTITY_H
#define BOXENTITY_H

#include <string>
#include <vector>

using namespace std;

class BoxEntity
{
public:
    int id;
    string name;

    BoxEntity()
    {
      // ctor
    }

    BoxEntity(int id, string name)
    {
        this->id = id;
        this->name = name;
    }
};

static const int BOX_PENDING_ID = 0;
static const int BOX_1_ID = 1;
static const int BOX_2_ID = 2;
static const int BOX_3_ID = 3;
static const int BOX_4_ID = 4;
static const int BOX_5_ID = 5;
static const int BOX_LEARNED_CARDS_ID = 6;

static const string BOX_PENDING_NAME = "PENDING";
static const string BOX_1_NAME = "BOX 1";
static const string BOX_2_NAME = "BOX 2";
static const string BOX_3_NAME = "BOX 3";
static const string BOX_4_NAME = "BOX 4";
static const string BOX_5_NAME = "BOX 5";
static const string BOX_LEARNED_CARDS_NAME = "LEARNED CARDS";

static const int NUM_BOXES = 7;
static const BoxEntity BOXES[7] = {
    BoxEntity(BOX_PENDING_ID, BOX_PENDING_NAME),
    BoxEntity(BOX_1_ID, BOX_1_NAME),
    BoxEntity(BOX_2_ID, BOX_2_NAME),
    BoxEntity(BOX_3_ID, BOX_3_NAME),
    BoxEntity(BOX_4_ID, BOX_4_NAME),
    BoxEntity(BOX_5_ID, BOX_5_NAME),
    BoxEntity(BOX_LEARNED_CARDS_ID, BOX_LEARNED_CARDS_NAME)
};

#endif // BOXENTITY_H
