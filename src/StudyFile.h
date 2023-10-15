#ifndef STUDYFILE_H
#define STUDYFILE_H

#include <vector>
#include "Box.h"
#include "TopicCardEntity.h"

using namespace std;

class StudyFile
{
public:
    Box getBox(int indexBox);
    TopicCardEntity getCard(int indexBox);
    bool hasRoom(int indexBox);
    bool hasCards(int indexBox);
    bool hasCards(void);
    void addCardToBox(int indexBox, TopicCardEntity card);
    void deleteCardFromBox(int indexBox);

    void initBoxes(int boxSizes[5]);
    void boxesStatus(void);

private:
    Box boxes[5];
};

#endif // STUDYFILE_H
