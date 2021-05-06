#include "HighScores.h"

HighScores::HighScores() {
}

void HighScores::SaveScore(string name, int score) {
    ofstream highScoresFile;

    highScoresFile.open("highscores.txt", ios::app);

    if (highScoresFile.is_open())
    {
        highScoresFile << name << " " << score << "\n";

        highScoresFile.close();
    }
    else
    {
        cout << "Unable to open highscores";
    }
}

void HighScores::GetHighScores(int amount)
{
    ifstream highScoresFile;

    highScoresFile.open("highscores.txt");

    if (highScoresFile.is_open())
    {
        vector<pair<int, string>> scoreVector;
        string name;
        int score;

        while (highScoresFile >> name >> score)
        {
            scoreVector.emplace_back(score, name);
        }

        highScoresFile.close();

        sort(scoreVector.begin(), scoreVector.end());
        reverse(scoreVector.begin(), scoreVector.end());
        cout << "\n" << "Top 10 High Scores: " << "\n";

        if (amount > scoreVector.size())
        {
            amount = scoreVector.size();
        }

        for (int i = 0; i < amount; i++)
        {
            string name_out = scoreVector[i].second;
            int score_out = scoreVector[i].first;
            cout << "Name: " << name_out << " | Score: " << score_out << endl;
        }
    }
    else
    {
        cout << "Unable to open highscores";
    }
}