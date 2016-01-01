#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
    std::string name;
    int strength;
    int charisma;
    int speed;

public:
    std::string getName();
    void setName(std::string name);
    virtual int getStrength();
    void setStrength(int strength);
    virtual int getCharisma();
    void setCharisma(int charisma);
    virtual int getSpeed();
    void setSpeed(int speed);
};
#endif
