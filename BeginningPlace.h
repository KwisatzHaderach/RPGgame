#ifndef BEGINNING_PLACE_H
#define BEGINNING_PLACE_H

#include "Place.h"
#include <vector>
#include <string>
#include "variables.h"

class BeginningPlace : public Place {
public:
    static std::vector<std::string> choose_text;
    static std::vector<std::vector<std::string>> choose_answers;

    BeginningPlace();
    std::string getType();
};
#endif
