#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

class Shop {
public:
    Shop(int _startAmount);
    ~Shop();
    bool isCoinsEmpty();
    void SetCoins(int _amount);
    void UpdateCoins(int _amount);
    int GetCoins();
    bool isBoughtPlayer(int _playerID);
    void BuyPlayer(int _playerID);
    void SetActivePlayer(int _playerID);
    int GetActivePlayer();
private:
    int coins;
};
