#pragma once
#include "Inventory.h"
#include <iostream>
#include <string>

using namespace std;

class NPC {
public:
    NPC(string _name, int _strength);
    ~NPC();
    //void AddItem(string _item, int _amount);
    int GetStrength();
    string GetName();
    void SetInventory(string item, int _amount);
    void GetInventory();
private:
    Inventory* inventory = new Inventory();
    //vector<string> backpack;
    int strength;
    string name;
};
