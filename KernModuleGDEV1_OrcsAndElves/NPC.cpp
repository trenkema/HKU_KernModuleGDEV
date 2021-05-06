#include "NPC.h"

NPC::NPC(string _name) {
    name = _name;
}

int NPC::GetStrength() {
    return strength;
}

string NPC::GetName() {
    return name;
}