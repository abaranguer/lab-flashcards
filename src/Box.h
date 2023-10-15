#ifndef BOX_H
#define BOX_H

#include <vector>
#include "BoxEntity.h"

#include "TopicCardEntity.h"

using namespace std;

class Box
{
public:
    Box();
    Box(BoxEntity boxEntity, int maxNumOfCards);
    bool hasRoom(void);
    bool addCard(TopicCardEntity card);
    bool removeCard(void);
    bool hasCards(void);
    TopicCardEntity getFirstCard(void);
    int getNumOfCards(void);
    int getMaxNumOfCards(void);

private:
    BoxEntity boxEntity;
    vector<TopicCardEntity> cards;
    int maxNumOfCards;
};

#endif // BOX_H
