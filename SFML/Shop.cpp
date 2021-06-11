#include "Shop.h"

Shop::Shop(int _startAmount) {
    this->coins = 0;

    if (isCoinsEmpty())
        SetCoins(_startAmount);
}

Shop::~Shop() {}

bool Shop::isCoinsEmpty()
{
    ifstream coinsFile;
    coinsFile.open("coinsamount.txt");

    if (coinsFile.is_open())
    {
        vector<int> coinsVector;
        int coinsAmount;

        while (coinsFile >> coinsAmount)
        {
            coinsVector.emplace_back(coinsAmount);
        }

        coinsFile.close();

        sort(coinsVector.begin(), coinsVector.end());

        if (coinsVector.size() == 0)
            return true;
    }

    return false;
}

void Shop::SetCoins(int _amount)
{
    this->coins = _amount;

    ofstream coinsFile;
    coinsFile.open("coinsamount.txt", ios::app);

    if (coinsFile.is_open())
    {
        coinsFile << this->coins;
        coinsFile.close();
    }
    else
    {
        cout << "Unable to open coinsFile";
    }
}

void Shop::UpdateCoins(int _amount) {
    this->coins += _amount;

    ofstream coinsFile;
    coinsFile.open("coinsamount.txt", std::ofstream::out | std::ofstream::trunc);

    if (coinsFile.is_open())
    {
        coinsFile << this->coins;
        coinsFile.close();
    }
    else
    {
        cout << "Unable to open coinsFile";
    }
}

int Shop::GetCoins() {
    ifstream coinsFile;
    coinsFile.open("coinsamount.txt");

    if (coinsFile.is_open())
    {
        vector<int> coinsVector;
        int coinsAmount;

        while (coinsFile >> coinsAmount)
        {
            coinsVector.emplace_back(coinsAmount);
        }

        coinsFile.close();

        if (!coinsVector.empty()) {
            this->coins = coinsVector[0];
        }
    }
    else
    {
        cout << "Unable to open coinsFile";
    }

    return this->coins;
}

bool Shop::isBoughtPlayer(int _playerID)
{
    ifstream shopDataFile;
    shopDataFile.open("shopdata.txt");

    if (shopDataFile.is_open())
    {
        vector<pair<int, bool>> playersVector;
        int playerID;
        bool isBought;

        while (shopDataFile >> playerID >> isBought)
        {
            playersVector.emplace_back(playerID, isBought);
        }

        shopDataFile.close();

        if (!playersVector.empty()) {
            for (int i = 0; i < playersVector.size(); ++i) {
                if (playersVector[i].first == _playerID)
                {
                    bool isBought_Out = playersVector[i].second;
                    if (isBought_Out) return true;
                }
            }
        }
    }
    else
    {
        cout << "Unable to open ShopData";
    }

    return false;
}

void Shop::BuyPlayer(int _playerID)
{
    ofstream shopDataFile;

    shopDataFile.open("shopdata.txt", ios::app);

    if (shopDataFile.is_open())
    {
        shopDataFile << _playerID << " " << true << "\n";

        shopDataFile.close();
    }
    else
    {
        cout << "Unable to open ShopData";
    }
}

void Shop::SetActivePlayer(int _playerID)
{
    ofstream activePlayerFile;
    activePlayerFile.open("activeplayer.txt",  std::ofstream::out | std::ofstream::trunc);

    if (activePlayerFile.is_open())
    {
        activePlayerFile << _playerID;
        activePlayerFile.close();

        activePlayerFile.close();
    }
    else
    {
        cout << "Unable to open ActivePlayerFile";
    }
}

int Shop::GetActivePlayer() {
    ifstream activePlayerFile;
    activePlayerFile.open("activeplayer.txt");

    if (activePlayerFile.is_open())
    {
        vector<int> activePlayerVector;
        int playerID;

        while (activePlayerFile >> playerID)
        {
            activePlayerVector.emplace_back(playerID);
        }

        activePlayerFile.close();

        if (!activePlayerVector.empty()) {
            return activePlayerVector[0];
        }
        else
        {
            SetActivePlayer(0);
            return 0;
        }
    }
    else
    {
        cout << "Unable to open ActivePlayerFile";
    }

    return 0;
}

