#include <iostream>
#include <limits>
#include "Orc.h"
#include "Elf.h"

void CallOrc() {
    string _name;
    int _strength;
    int _thorns;
    cout << "How do you call your Orc: ";
    cin >> _name;
    cout << "\n" << "What is the Strength of your Orc: ";
    cin >> _strength;

    while (cin.fail()) {
        cout << "Only enter numbers." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> _strength;
    }

    cout << "\n" << "How many Thorns does your Orc have: ";
    cin >> _thorns;

    while (cin.fail()) {
        cout << "Only enter numbers." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> _thorns;
    }

    Orc orc = Orc(_name, _strength);
    orc.SetThorns(_thorns);
    cout << "\n" << "Your Orc's name is: " << orc.GetName() << ". With a Strength of: " << orc.GetStrength() << " and " << orc.GetThorns() << " Thorns." << endl;

    orc.SetInventory("Steel Axe", 1);
    orc.SetInventory("Dildo", 3);
    orc.SetInventory("Hoes", 2);
    orc.GetInventory();
    system("PAUSE");
}

void CallElf() {
    string _name;
    int _strength;
    int _magic;
    cout << "How do you call your Elf: ";
    cin >> _name;
    cout << "\n" << "What is the Strength of your Elf: ";
    cin >> _strength;

    while (cin.fail()) {
        cout << "Only enter numbers." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> _strength;
    }

    cout << "\n" << "What is the Magic Power of your Elf: ";
    cin >> _magic;

    while (cin.fail()) {
        cout << "Only enter numbers." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> _magic;
    }

    Elf elf = Elf(_name, _strength);
    elf.SetMagic(_magic);

    cout << "\n" << "Your Elf's name is: " << elf.GetName() << ". With a Strength of: " << elf.GetStrength() << " and a Magic Power of: " << elf.GetMagic() << "." << endl;
    elf.SetInventory("Magic Wand", 1);
    elf.GetInventory();
    system("PAUSE");
}

int main() {
    CallOrc();
    CallElf();
}
