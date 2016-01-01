#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <iostream>
#include "Item.h"

class Inventory {
private:
    int capacity;
    int itemCount;
    std::vector<Item*> items;

public:
    Inventory(int capacity);
    int getCapacity();
    void setCapacity(int capacity);
    int getItemCount();
    void setItemCount(int itemCount);
    std::vector<Item*> getItems();
    Item* getItem(std::string item_name);
    void addItem(Item* item);
    void removeItem(Item* item);
    void removeItem(std::string name);
    void printInventory();
    bool isItemInInventory(std::string item_name);
    ~Inventory();
};
#endif
