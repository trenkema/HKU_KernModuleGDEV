#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string line;
    ifstream file1, file2;
    ofstream file3;

    file1.open("file1.txt");
    file2.open("file2.txt");
    file3.open("file3.txt");

    if (file1.is_open() && file2.is_open() && file3.is_open())
    {
        while (!file1.eof() || !file2.eof())
        {
            if (getline(file1, line))
                file3 << line << "\n";
            if (getline(file2, line))
                file3 << line << "\n";
        }
    }
    else
    {
        cout << "Couldn't Open file: file1.txt, file2.txt or file3.txt" << endl;
    }

    file1.close();
    file2.close();
    file3.close();
}
