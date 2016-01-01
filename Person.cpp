#include "Person.h"

using namespace std;

string Person::getName() {
    return this->name;
}

void Person::setName(string name) {
    this->name = name;
}

int Person::getStrength() {
    return this->strength;
}

void Person::setStrength(int strength) {
    this->strength = strength;
}

int Person::getCharisma() {
    return this->charisma;
}

void Person::setCharisma(int charisma) {
    this->charisma = charisma;
}

int Person::getSpeed() {
    return this->speed;
}

void Person::setSpeed(int speed) {
    this->speed = speed;
}
