#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include "Item.h"
#include "NPC.h"
#include <time.h>
#include <map>
#include "variables.h"

class Place {
private:
    int getClosestYear(int year);

protected:
    Place* wayBack;
    std::vector<Place*> wayForth;
    Item* item;
    NPC* being;
    std::string text;
    std::vector<std::string> answers;

public:
    static std::vector<std::vector<std::string>> choose_text;
    static std::vector<std::vector<std::string>> choose_answers;

    Place(Place* wayBack);
    Place();
    Place* getWayBack();
    std::vector<Place*> getWayForth();
    void addWayForth(Place* place);
    Item* getItem();
    void removeItem();
    NPC* getBeing();
    void removeBeing();
    void printTextWithAnswers();
    int getAnswersSize();
    void setText();
    virtual std::string getType();
    ~Place();
};
#endif
