#include "Box.h"

using namespace std;

Box::Box(void)
{
    // Empty constructor
}

Box::Box(BoxEntity boxEntity, int maxNumOfCards)
{
    this->boxEntity = boxEntity;
    this->maxNumOfCards = maxNumOfCards;
}

bool Box::hasRoom(void)
{
    bool retValue = false;

    if (getNumOfCards() < maxNumOfCards)
    {
        retValue = true;
    }

    return retValue;
}

bool Box::addCard(TopicCardEntity card)
{
    bool retValue = false;

    if (hasRoom())
    {
        cards.push_back(card);
        retValue = true;
    }

    return retValue;
}

bool Box::hasCards(void)
{
    return !(cards.empty());
}

bool Box::removeCard(void)
{
    bool retValue = false;

    if (hasCards()) {
        cards.erase(cards.begin());
        retValue = true;
    }

    return retValue;
}

TopicCardEntity Box::getFirstCard(void)
{
    return cards.at(0);
}

int Box::getNumOfCards(void)
{
    return cards.size();
}

int Box::getMaxNumOfCards(void)
{
    return maxNumOfCards;
}
