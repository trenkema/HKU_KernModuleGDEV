#pragma once
#include "NPC.h"
#include <string>

using namespace std;

class Orc : public NPC {
public:
    Orc(string name, int strength) : NPC(name, strength) {};
    int GetThorns();
    void SetThorns(int _thorns);
private:
    int thorns;
};
