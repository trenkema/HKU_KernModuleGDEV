#include "NPC.h"

NPC::NPC(string _name, int _strength) {
    name = _name;
    strength = _strength;
}

int NPC::GetStrength() {
    return strength;
}

string NPC::GetName() {
    return name;
}

//void NPC::AddItem(string _item, int _amount) {
//    cout << NPC::name << " has collected the item: " << _item << " " << _amount << "x \n";
//    for (int i = 0; i < _amount; ++i) {
//        backpack.push_back(_item);
//    }
//}

NPC::~NPC() {
    cout << NPC::name << " has been Destroyed" << "\n";
}

void NPC::SetInventory(string item, int _amount) {
    cout << NPC::name << " has collected the item: " << item << " " << _amount << "x \n";
    for (int i = 0; i < _amount; i++)
    {
        inventory->inventoryList.push_back(item);
    }
}

void NPC::GetInventory() {
    cout << "In " << name << " it's inventory is: " << endl;
    for (string i : inventory->inventoryList)
    {
        cout << i << endl;
    }
}