#pragma once
#include "NPC.h"
#include <string>

using namespace std;

class Elf : public NPC {
public:
    Elf(string name, int strength) : NPC(name, strength) {};
    int GetMagic();
    void SetMagic(int _magic);
private:
    int magic;
};
