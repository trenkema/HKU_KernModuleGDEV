#include <iostream>
#include "Orc.h"

int main() {
    string _name;
    cout << "How do you call your Orc: " << endl;
    cin >> _name;
    Orc orc = Orc(_name);
    cout << orc.GetName() << endl;
}
