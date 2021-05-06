#include "SimonSays.h"
#include <ctime>

HighScores highScores = HighScores();

SimonSays::SimonSays() {
    score = 0;
    patternLength = 3;
    intPattern.clear();
    inputPattern.clear();
    cout << "Welcome to Simon Says!" << endl;
    cout << "Please enter your name: ";
    getline(cin, inputName);
    inputName = CheckInput(inputName);

    system("PAUSE");
}

string SimonSays::CheckInput(string input)
{
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

    if (input.empty())
    {
        input = "Unknown";
    }

    return input;
}

void SimonSays::StartGame() {
    while (true)
    {
        intPattern = GeneratePattern(intPattern);
        cout << "The pattern: " << intPattern << "\n";
        _sleep(2000);
        system("CLS");
        cout << "Please enter " << intPattern.size() << " characters to match: ";
        cin >> inputPattern;

        if (inputPattern != intPattern)
        {
            highScores.SaveScore(inputName, score);
            cout << "Sorry, you lose. The correct sequence was: " << intPattern << "\n";
            cout << "Your score is: " << score << "\n";
            highScores.GetHighScores(10);
            system("PAUSE");
            break;
        }

        score++;
        patternLength = 1;
    }
}

string SimonSays::GeneratePattern(string oldPattern)
{
    srand (time (0));
    string totalPattern;
    totalPattern = oldPattern;
    int randomInt = 0;

    for (int i = 0; i < patternLength; ++i) {
        randomInt = rand() % 10;
        totalPattern += to_string(randomInt);
    }

    return totalPattern;
}

