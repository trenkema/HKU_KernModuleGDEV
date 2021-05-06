#pragma once
#include "HighScores.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

class HighScores
{
public:
    HighScores();
    void SaveScore(string name, int score);
    void GetHighScores(int amount);
private:
};