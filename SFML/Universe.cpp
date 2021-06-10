#include "Universe.h"

Universe::Universe(int width, int height) {
    this->window = nullptr;
    this->InitVariables(width, height);
    this->InitWindow();
    this->InitFonts();
    this->InitText();
    this->InitImages();
    //this->InitSounds();
    this->SpawnPlayer();
    this->SpawnObstacles();
}

Universe::~Universe() {
    delete this->window;
}

void Universe::InitVariables(int width, int height) {
    this->width = width;
    this->height = height;
    this->hasBegan = false;
    this->endGame = false;
    this->score = 0;
    this->health = 1;
    this->obstacleSpawnTimer = 0.f;
    this->obstacleSpawnTimerMax = 50.f;
    this->maxObstacles = 10;
}

void Universe::InitImages() {
    if (!beginTexture.loadFromFile("../BGMainMenu.jpg"))
    {
        std::cout << "Failed to load BG!" << "\n";
    }

    if (!inGameTexture.loadFromFile("../BGInGame.png"))
    {
        std::cout << "Failed to load BG!" << "\n";
    }

    if (!endTexture.loadFromFile("../BGEndGame.png"))
    {
        std::cout << "Failed to load BG!" << "\n";
    }
}

void Universe::InitSounds() {
    if (!this->positiveBuffer.loadFromFile("../Positive.wav"));
    {
        std::cout << "Failed to load Positive Sound!" << "\n";
    }

    if (!this->negativeBuffer.loadFromFile("../Negative.wav"));
    {
        std::cout << "Failed to load Negative Sound!" << "\n";
    }
}

void Universe::InitWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Dream Catcher!");
    this->window->setFramerateLimit(60);
}

void Universe::InitFonts() {
    if (!this->font.loadFromFile("../Fonts/ADELIA.otf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
    }
}

void Universe::InitText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(20);
    this->uiText.setFillColor(sf::Color::Yellow);
    this->uiText.setString("");
    this->uiText.setPosition(20, 20);

    this->beginTextTop.setFont(this->font);
    this->beginTextTop.setCharacterSize(65);
    this->beginTextTop.setFillColor(sf::Color::Yellow);
    this->beginTextTop.setString("");

    this->beginTextBottom.setFont(this->font);
    this->beginTextBottom.setCharacterSize(40);
    this->beginTextBottom.setFillColor(sf::Color::White);
    this->beginTextBottom.setString("");

    this->endTextTop.setFont(this->font);
    this->endTextTop.setCharacterSize(65);
    this->endTextTop.setFillColor(sf::Color::Red);
    this->endTextTop.setString("");

    this->endTextMiddle.setFont(this->font);
    this->endTextMiddle.setCharacterSize(40);
    this->endTextMiddle.setFillColor(sf::Color::Green);
    this->endTextMiddle.setString("");

    this->endTextBottom.setFont(this->font);
    this->endTextBottom.setCharacterSize(45);
    this->endTextBottom.setFillColor(sf::Color::White);
    this->endTextBottom.setString("");
}

const bool Universe::Running() const {
    return this->window->isOpen();
}

void Universe::UpdateText() {
    std::stringstream ss;

    ss << "Wishes: " << this->score << "\n" << "Misfortune: " << this->health << "\n";

    this->uiText.setString(ss.str());
}

void Universe::UpdateObstacles()
{
    if (this->obstacles.size() < this->maxObstacles) {
        if (this->obstacleSpawnTimer >= this->obstacleSpawnTimerMax) {
            this->SpawnObstacles();
            this->obstacleSpawnTimer = 0.f;
        } else {
            this->obstacleSpawnTimer += 1.f;
        }
    }

    for (int i = 0; i < this->obstacles.size(); i++) {
        bool dead = false;

        this->obstacles[i].move();

        if(player.isCollidingWithObstacle(obstacles[i]))
        {
            dead = true;

            //sf::Sound sound;
            //obstacles[i].DoesDealDamage() ? sound.setBuffer(negativeBuffer) : sound.setBuffer(positiveBuffer);
            //sound.play();

            obstacles[i].DoesDealDamage() ? this->health -= obstacles[i].GetDamagePoints() : this->score += obstacles[i].GetScorePoints();
            //this->score += obstacles[i].GetScorePoints() > 0 ? obstacles[i].GetScorePoints() : obstacles[i].GetDamagePoints();
            std::cout << "Wishes: " << this->score << "\n";
        }

        if (obstacles[i].isNotCatched(height))
        {
            dead = true;

//            sf::Sound sound;
//            obstacles[i].GetDamagePoints() > 0 ? sound.setBuffer(positiveBuffer) : sound.setBuffer(negativeBuffer);
//
//            this->health -= obstacles[i].GetDamagePoints();
//            std::cout << "Misfortune: " << this->health << "\n";
        }

        if (dead)
        {
            this->obstacles.erase(this->obstacles.begin() + i);
        }

        obstacles[i].isCollidingWithBounds(width);
    }
}

void Universe::SpawnPlayer() {
    this->player.setSpeed(2);
    this->player.setSize(80, 50);
    this->player.setPos({float(this->width/2) - 20, float(this->height) - 65});
}

void Universe::SpawnObstacles() {
    int randomDirection = rand() % 2;
    if (randomDirection == 1)
        this->obstacle.setSpeed(-1.f, 1.f);
    else
        this->obstacle.setSpeed(1.f, 1.f);

    int type = rand() % 4;

    this->obstacle.SetType(type);

    rand() % (width - int(obstacle.getSize().x));
    float randomFloat = rand() % (width - int(obstacle.getSize().x));

    if (randomFloat <= obstacle.getSize().x / 1.5f)
    {
        randomFloat += obstacle.getSize().x;
    }

    this->obstacle.setPos({(randomFloat - this->obstacle.getSize().x),0});

    this->obstacles.push_back(this->obstacle);
}

const bool Universe::GetEndGame() const {
    return this->endGame;
}

void Universe::PollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                if (this->ev.key.code == sf::Keyboard::Space && !hasBegan && !endGame)
                {
                    hasBegan = true;
                }
                if (this->ev.key.code == sf::Keyboard::R && endGame) {
                    ResetGame();
                    hasBegan = false;
                    endGame = false;
                }
                break;
        }
    }
}

void Universe::Update() {
    this->PollEvents();

    if (!this->endGame && this->hasBegan)
    {
        this->player.move();
        this->UpdateObstacles();
        this->UpdateText();
    }

    if (this->health <= 0)
    {
        this->endGame = true;
    }
}

void Universe::DrawText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Universe::DrawObstacles(sf::RenderTarget& target) {
    for (auto &e : this->obstacles)
    {
        int tempTypeID = e.GetTypeID();
        sf::RectangleShape shape = e.GetObstacle();
        switch (tempTypeID) {
            case 0:
                enemyTexture.loadFromFile("../NormalStar.png");
                break;
            case 1:
                enemyTexture.loadFromFile("../SuperStar.png");
                break;
            case 2:
                enemyTexture.loadFromFile("../EnemyStar.png");
                break;
            case 3:
                enemyTexture.loadFromFile("../EnemyStar.png");
                break;
        }

        shape.setTexture(&enemyTexture);
        target.draw(shape);
    }
}

void Universe::BeginScreen(sf::RenderTarget& target)
{
    std::stringstream ssTop;
    std::stringstream ssBottom;

    ssTop << "Dream Catcher!";
    ssBottom << "Press Spacebar To Play";

    this->beginTextTop.setString(ssTop.str());
    this->beginTextBottom.setString(ssBottom.str());

    sf::FloatRect textRect = beginTextTop.getLocalBounds();
    beginTextTop.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top + textRect.height/2.0f);
    beginTextTop.setPosition(sf::Vector2f(this->width/2.0f, this->height/2.0f * 0.7));

    sf::FloatRect textRect2 = beginTextBottom.getLocalBounds();
    beginTextBottom.setOrigin(textRect2.left + textRect2.width/2.0f,
                              textRect2.top + textRect2.height/2.0f);
    beginTextBottom.setPosition(sf::Vector2f(this->width/2.0f, this->height/2.0f * 1.3));

    sf::Sprite background(this->beginTexture);
    float a = (float) this->window->getSize().x/(float) beginTexture.getSize().x;
    float b = (float) this->window->getSize().y/(float) beginTexture.getSize().y;
    background.scale(a, b);
    target.draw(background);
    target.draw(this->beginTextTop);
    target.draw(this->beginTextBottom);
}

void Universe::EndScreen(sf::RenderTarget& target)
{
    std::stringstream ss;
    std::stringstream ss2;
    std::stringstream ss3;

    ss << "No More Wishes";
    ss2 << "Wishes: " << this->score;
    ss3 << "Press R To Return To Main Menu";

    this->endTextTop.setString(ss.str());
    this->endTextMiddle.setString(ss2.str());
    this->endTextBottom.setString(ss3.str());

    sf::FloatRect textRect = endTextTop.getLocalBounds();
    endTextTop.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top + textRect.height/2.0f);
    endTextTop.setPosition(sf::Vector2f(this->width/2.0f, this->height/2.0f * 0.4));

    sf::FloatRect textRect2 = endTextMiddle.getLocalBounds();
    endTextMiddle.setOrigin(textRect2.left + textRect2.width/2.0f,
                         textRect2.top + textRect2.height/2.0f);
    endTextMiddle.setPosition(sf::Vector2f(this->width/2.0f, this->height/2.0f));

    sf::FloatRect textRect3 = endTextBottom.getLocalBounds();
    endTextBottom.setOrigin(textRect3.left + textRect3.width/2.0f,
                         textRect3.top + textRect3.height/2.0f);
    endTextBottom.setPosition(sf::Vector2f(this->width/2.0f, this->height/2.0f * 1.6));

    sf::Sprite background(this->endTexture);
    float a = (float) this->window->getSize().x/(float) endTexture.getSize().x;
    float b = (float) this->window->getSize().y/(float) endTexture.getSize().y;
    background.scale(a, b);
    target.draw(background);

    target.draw(this->endTextTop);
    target.draw(this->endTextMiddle);
    target.draw(this->endTextBottom);
}

void Universe::InGame(sf::RenderTarget &target) {
    sf::Sprite background(this->inGameTexture);
    float a = (float) this->window->getSize().x/(float) inGameTexture.getSize().x;
    float b = (float) this->window->getSize().y/(float) inGameTexture.getSize().y;
    background.scale(a, b);

    target.draw(background);
    this->player.drawTo(this->window);
    this->DrawObstacles(*this->window);
    this->DrawText(*this->window);
}

void Universe::ResetGame() {
    this->InitVariables(this->width, this->height);

    for (int i = 0; i < this->obstacles.size(); i++) {
        this->obstacles.erase(this->obstacles.begin() + i);
    }

    obstacles.clear();
}

void Universe::Draw()
{
    this->window->clear();

    if (!this->hasBegan)
    {
        BeginScreen(*this->window);
    }
    else if (this->endGame)
    {
        EndScreen(*this->window);
    }
    else
    {
        InGame(*this->window);
    }

    this->window->display();
}