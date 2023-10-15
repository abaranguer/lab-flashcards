#include <iostream>
#include "StudyFile.h"

using namespace std;

void StudyFile::initBoxes(int boxSizes[5])
{
    for(int i = 0; i < 5; i++)
    {
        Box box(BOXES[i], boxSizes[i]);
        boxes[i] = box;
    }
}

Box StudyFile::getBox(int indexBox)
{
    return boxes[indexBox];
}

TopicCardEntity StudyFile::getCard(int indexBox)
{
    return boxes[indexBox].getFirstCard();
}

bool StudyFile::hasRoom(int indexBox)
{
    return boxes[indexBox].hasRoom();
}

bool StudyFile::hasCards(void)
{
    bool hasCards = false;

    for(int indexBox = 0; indexBox < 5; indexBox++) {
        hasCards = hasCards || boxes[indexBox].hasCards();
    }

    return hasCards;
}


bool StudyFile::hasCards(int indexBox)
{
    return boxes[indexBox].hasCards();
}

void StudyFile::deleteCardFromBox(int indexBox)
{
    boxes[indexBox].removeCard();
}

void StudyFile::addCardToBox(int indexBox, TopicCardEntity card)
{
    boxes[indexBox].addCard(card);
}

void StudyFile::boxesStatus(void)
{
    for (int i = 0; i < 5; i++)
    {
        cout << "    box " << i
            << ". " << boxes[i].getNumOfCards()
            << " / " << boxes[i].getMaxNumOfCards() << endl;
    }
}
