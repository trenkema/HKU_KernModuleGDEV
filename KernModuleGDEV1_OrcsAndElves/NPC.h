#pragma once
#include <string>

using namespace std;

class NPC {
public:
    NPC(string _name);
    int GetStrength();
    string GetName();
private:
    int strength;
    string name;
};
