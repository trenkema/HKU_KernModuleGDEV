#pragma once
#include "SimonSays.h"
#include "HighScores.h"
#include <iostream>
#include <string>

using namespace std;

class SimonSays
{
public:
    SimonSays();
    string CheckInput(string input);
    void StartGame();
    string GeneratePattern(string oldPattern);
private:
    string inputName;
    int score;
    string intPattern;
    int patternLength;
    string inputPattern;
};