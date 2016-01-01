#include "Inventory.h"

using namespace std;

Inventory::Inventory(int capacity) {
    this->capacity = capacity;
    this->itemCount = 0;
    this->items.reserve(this->capacity);
}

int Inventory::getCapacity() {
    return this->capacity;
}

void Inventory::setCapacity(int capacity) {
    this->capacity = capacity;
}

int Inventory::getItemCount() {
    return this->itemCount;
}

void Inventory::setItemCount(int itemCount) {
    this->itemCount = itemCount;
}

vector<Item*> Inventory::getItems() {
    return this->items;
}

Item* Inventory::getItem(std::string item_name) {
    if (this->isItemInInventory(item_name))
        for (unsigned int i = 0; i < this->items.size(); ++i)
            if (this->items[i]->getName() == item_name)
                return this->items[i];
}

void Inventory::addItem(Item* item) {
    this->items.push_back(item);
}

void Inventory::removeItem(Item* item) {
    for (vector<Item*>::iterator i = this->items.begin();
            i != this->items.end(); ++i)
        if (*i == item) {
            delete *i;
            this->items.erase(i);
        }
}

void Inventory::removeItem(string name) {
    for (unsigned int i = 0; i < this->items.size(); ++i)
        if (this->items[i]->getName() == name) {
            delete this->items[i];
            this->items.erase(this->items.begin() + i);
        }
}

void Inventory::printInventory() {
    cout << endl << "==================================================";
    cout << endl << "This is content of your inventory:" << endl;
    cout << "Item name: Strength/Charisma/Speed/Special/Type" << endl;
    for (int i = 0; i < this->itemCount; ++i)
        this->items[i]->printInfo();
    cout << "==================================================" << endl;
    cout << endl;
}

bool Inventory::isItemInInventory(string item_name) {
    for (int i = 0; i < this->itemCount; ++i)
        if (this->items[i]->getName() == item_name)
            return true;
    return false;
}

Inventory::~Inventory() {
    for (unsigned int i = 0; i < this->items.size(); ++i)
        delete this->items[i];
    this->items.clear();
}
