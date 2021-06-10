#include <ctgmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Obstacle.h"
#include "Player.h"
#include <vector>
#include <sstream>

class Universe {
public:
    Universe(int width, int height);
    virtual ~Universe();

    const bool Running() const;
    const bool GetEndGame() const;
    void PollEvents();
    void Update();

    void UpdateObstacles();
    void UpdateText();
    void SpawnPlayer();
    void SpawnObstacles();

    void BeginScreen(sf::RenderTarget& target);
    void EndScreen(sf::RenderTarget& target);
    void InGame(sf::RenderTarget& target);
    void ResetGame();

    void DrawText(sf::RenderTarget& target);
    void DrawObstacles(sf::RenderTarget& target);
    void Draw();
private:
    void InitVariables(int width, int height);
    void InitFonts();
    void InitText();
    void InitImages();
    void InitSounds();
    void InitWindow();
    int width, height;
    sf::RenderWindow* window;
    sf::Event ev;
    Player player;
    Obstacle obstacle;
    std::vector<Obstacle> obstacles;

    sf::Font font;
    sf::Text uiText;
    sf::Text beginTextTop;
    sf::Text beginTextBottom;
    sf::Text endTextTop;
    sf::Text endTextMiddle;
    sf::Text endTextBottom;
    sf::Texture beginTexture;
    sf::Texture inGameTexture;
    sf::Texture endTexture;
    sf::Texture enemyTexture;

    bool hasBegan;
    bool endGame;
    float obstacleSpawnTimer, obstacleSpawnTimerMax;
    int maxObstacles;
    int score;
    int health;

    sf::SoundBuffer positiveBuffer;
    sf::SoundBuffer negativeBuffer;
};
