#include <ctgmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include "Obstacle.h"
#include "Player.h"
#include "DeltaTime.h"
#include "SoundManager.h"
#include "Shop.h"

class Universe {
public:
    Universe(int _width, int _height);
    virtual ~Universe();

    void BeginScreen(sf::RenderTarget& target);
    void ShopScreen(sf::RenderTarget &target);
    void InGame(sf::RenderTarget& target);
    void PausedScreen(sf::RenderTarget& target);
    void EndScreen(sf::RenderTarget& target);

    void SetActivePlayerText(sf::RenderTarget &target);
    void SpawnPlayer();
    void SpawnObstacles();
    void UpdateObstacles();
    void UpdateText();
    void SetCenterText(sf::Text& _text, std::stringstream& _stream, float _offSet);

    void PollEvents();
    void Update();

    bool Running() const;
    bool GetEndGame() const;

    void ResetGame();

    void DrawObstacles();
    void Draw();
private:
    void InitVariables(int _width, int _height);
    void InitFonts();
    void InitText();
    void InitImages();
    void InitSounds();
    void InitWindow();

    int width, height;

    SoundManager* soundManager;

    Shop* shop;

    DeltaTime* deltaTime;
    sf::RenderWindow* window;
    sf::Event ev;

    Player* player;
    Obstacle obstacle;
    std::vector<Obstacle> obstacles;

    sf::Font font;

    sf::Text uiText;
    sf::Text beginTextTop;
    sf::Text beginTextBottom;
    sf::Text beginTextShop;
    sf::Text shopText;
    sf::Text coinsText;
    sf::Text pausedText;
    sf::Text endTextTop;
    sf::Text endTextMiddle;
    sf::Text endTextBottom;

    sf::Texture beginTexture;
    sf::Texture inGameTexture;
    sf::Texture endTexture;

    sf::Texture _shopItemDefault;
    sf::Texture _shopItem1;
    sf::Texture _shopItem2;
    sf::RectangleShape shopItemDefault;
    sf::RectangleShape shopItem1;
    sf::RectangleShape shopItem2;
    sf::Text shopReturnText;
    sf::Text shopItemDefaultPrice;
    sf::Text shopItem1Price;
    sf::Text shopItem2Price;
    sf::Text playerSelectText;
    sf::Text activePlayerText;

    bool hasShopOpen;
    bool hasBegan;
    bool endGame;
    bool paused;

    float obstacleSpawnTimer, obstacleSpawnTimerMax;
    int maxObstacles;

    int activePlayer;
    int score;
    int health;
    int coins;
};
