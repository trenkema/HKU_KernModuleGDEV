#include "Universe.h"

Universe::Universe(int _width, int _height) {
    this->window = nullptr;
    this->shop = new Shop(5000);
    this->coins = this->shop->GetCoins();
    this->player = new Player(_width);
    this->deltaTime = new DeltaTime();
    this->InitVariables(_width, _height);
    this->InitWindow();
    this->InitFonts();
    this->InitText();
    this->InitImages();
    this->InitSounds();
    this->SpawnPlayer();
    this->SpawnObstacles();
}

// Destroy Pointers
Universe::~Universe() {
    delete this->window;
    delete this->deltaTime;
    delete this->soundManager;
    delete this->player;
    delete this->shop;
}

// Initialize Everything
void Universe::InitVariables(int _width, int _height) {
    this->width = _width;
    this->height = _height;
    this->activePlayer = this->shop->GetActivePlayer();
    this->player->SetTexture(this->activePlayer);
    this->hasShopOpen = false;
    this->hasBegan = false;
    this->endGame = false;
    this->paused = false;
    this->score = 0;
    this->health = 3;
    this->obstacleSpawnTimer = 0.f;
    this->obstacleSpawnTimerMax = 10.f;
    this->maxObstacles = 55;
}

void Universe::InitFonts() {
    if (!this->font.loadFromFile("../Fonts/ADELIA.otf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
    }
}

void Universe::InitText() {
    // In-Game Screen
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(20);
    this->uiText.setFillColor(sf::Color::Yellow);
    this->uiText.setString("");
    this->uiText.setPosition(20, 20);

    // Begin Screen
    this->beginTextTop.setFont(this->font);
    this->beginTextTop.setCharacterSize(65);
    this->beginTextTop.setFillColor(sf::Color::Yellow);
    this->beginTextTop.setString("");

    this->beginTextBottom.setFont(this->font);
    this->beginTextBottom.setCharacterSize(40);
    this->beginTextBottom.setFillColor(sf::Color::White);
    this->beginTextBottom.setString("");

    this->beginTextShop.setFont(this->font);
    this->beginTextShop.setCharacterSize(30);
    this->beginTextShop.setFillColor(sf::Color::Green);
    this->beginTextShop.setString("");

    // Shop Screen
    this->shopText.setFont(this->font);
    this->shopText.setCharacterSize(40);
    this->shopText.setFillColor(sf::Color::White);
    this->shopText.setString("");

    this->shopReturnText.setFont(this->font);
    this->shopReturnText.setCharacterSize(25);
    this->shopReturnText.setFillColor(sf::Color::White);
    this->shopReturnText.setString("");

    this->shopItemDefaultPrice.setFont(this->font);
    this->shopItemDefaultPrice.setCharacterSize(25);
    this->shopItemDefaultPrice.setFillColor(sf::Color::Green);
    this->shopItemDefaultPrice.setString("");
    this->shopItemDefaultPrice.setStyle(sf::Text::Bold);

    this->shopItem1Price.setFont(this->font);
    this->shopItem1Price.setCharacterSize(25);
    this->shopItem1Price.setFillColor(sf::Color::Green);
    this->shopItem1Price.setString("");
    this->shopItem1Price.setStyle(sf::Text::Bold);

    this->shopItem2Price.setFont(this->font);
    this->shopItem2Price.setCharacterSize(25);
    this->shopItem2Price.setFillColor(sf::Color::Green);
    this->shopItem2Price.setString("");
    this->shopItem2Price.setStyle(sf::Text::Bold);

    this->coinsText.setFont(this->font);
    this->coinsText.setCharacterSize(25);
    this->coinsText.setFillColor(sf::Color::Yellow);
    this->coinsText.setString("");
    this->coinsText.setStyle(sf::Text::Bold);

    this->playerSelectText.setFont(this->font);
    this->playerSelectText.setCharacterSize(30);
    this->playerSelectText.setFillColor(sf::Color::Red);
    this->playerSelectText.setString("");
    this->playerSelectText.setStyle(sf::Text::Bold);

    this->activePlayerText.setFont(this->font);
    this->activePlayerText.setCharacterSize(40);
    this->activePlayerText.setFillColor(sf::Color::Red);
    this->activePlayerText.setString("");

    // Pause Screen
    this->pausedText.setFont(this->font);
    this->pausedText.setCharacterSize(45);
    this->pausedText.setFillColor(sf::Color::White);
    this->pausedText.setString("");

    // End Screen
    this->endTextTop.setFont(this->font);
    this->endTextTop.setCharacterSize(65);
    this->endTextTop.setFillColor(sf::Color::Red);
    this->endTextTop.setString("");

    this->endTextMiddle.setFont(this->font);
    this->endTextMiddle.setCharacterSize(40);
    this->endTextMiddle.setFillColor(sf::Color::Green);
    this->endTextMiddle.setString("");

    this->endTextBottom.setFont(this->font);
    this->endTextBottom.setCharacterSize(40);
    this->endTextBottom.setFillColor(sf::Color::White);
    this->endTextBottom.setString("");
}

void Universe::InitImages() {
    if (!this->beginTexture.loadFromFile("../Images/BGMainMenu.jpg"))
    {
        std::cout << "Failed to load BG!" << "\n";
    }

    if (!this->inGameTexture.loadFromFile("../Images/BGInGame.png"))
    {
        std::cout << "Failed to load BG!" << "\n";
    }

    if (!this->endTexture.loadFromFile("../Images/BGEndGame.png"))
    {
        std::cout << "Failed to load BG!" << "\n";
    }

    if (!this->_shopItemDefault.loadFromFile("../Images/ShopItemDefault.png"))
    {
        std::cout << "Failed to load ShopItemDefault!" << "\n";
    }
    this->shopItemDefault.setTexture(&this->_shopItemDefault);
    this->shopItemDefault.setSize(sf::Vector2f(235, 225));

    if (!this->_shopItem1.loadFromFile("../Images/ShopItem1.png"))
    {
        std::cout << "Failed to load ShopItem1!" << "\n";
    }
    this->shopItem1.setTexture(&this->_shopItem1);
    this->shopItem1.setSize(sf::Vector2f(235, 225));

    if (!this->_shopItem2.loadFromFile("../Images/ShopItem2.png"))
    {
        std::cout << "Failed to load ShopItem2!" << "\n";
    }
    this->shopItem2.setTexture(&this->_shopItem2);
    this->shopItem2.setSize(sf::Vector2f(235, 225));
}

void Universe::InitSounds() {
    this->soundManager = new SoundManager();
}

void Universe::InitWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Dream Catcher!");
    this->window->setFramerateLimit(60);
    this->window->setKeyRepeatEnabled(false);
}

// Different States
void Universe::BeginScreen(sf::RenderTarget& target)
{
    std::stringstream ssTop;
    std::stringstream ssBottom;
    std::stringstream  ssBottomShop;

    ssTop << "Dream Catcher!";
    ssBottom << "Press Spacebar To Play";
    ssBottomShop << "Press Enter For Shop";

    SetCenterText(this->beginTextTop ,ssTop, 0.4);
    SetCenterText(this->beginTextBottom, ssBottom, 1.5);
    SetCenterText(this->beginTextShop, ssBottomShop, 1.7);

    sf::Sprite background(this->beginTexture);
    float a = (float) this->window->getSize().x/(float) this->beginTexture.getSize().x;
    float b = (float) this->window->getSize().y/(float) this->beginTexture.getSize().y;
    background.scale(a, b);
    target.draw(background);

    target.draw(this->beginTextTop);
    target.draw(this->beginTextBottom);
    target.draw(this->beginTextShop);
}

void Universe::ShopScreen(sf::RenderTarget &target)
{
    std::stringstream ssTop;
    std::stringstream ssCoins;
    std::stringstream ssPlayerSelect;
    std::stringstream ssItemDefaultPrice;
    std::stringstream ssItem1Price;
    std::stringstream ssItem2Price;
    std::stringstream ssReturn;

    ssTop << "Shop";
    ssCoins << "Your Coins: " << this->coins;
    ssPlayerSelect << "Press 1-3 To Select/Purchase Player";
    ssItemDefaultPrice << "0";
    ssItem1Price << "500";
    ssItem2Price << "1000";
    ssReturn << "Press Backspace To Return";

    this->coinsText.setString(ssCoins.str());
    this->playerSelectText.setString(ssPlayerSelect.str());
    this->shopItemDefaultPrice.setString(ssItemDefaultPrice.str());
    this->shopItem1Price.setString(ssItem1Price.str());
    this->shopItem2Price.setString(ssItem2Price.str());
    this->shopReturnText.setString(ssReturn.str());
    SetCenterText(this->shopText, ssTop, 0.3);
    SetCenterText(this->coinsText, ssCoins, 0.55);
    SetCenterText(this->playerSelectText, ssPlayerSelect, 1.85);
    SetCenterText(this->shopItemDefaultPrice, ssItemDefaultPrice, 1.325);
    SetCenterText(this->shopItem1Price, ssItem1Price, 1.325);
    SetCenterText(this->shopItem2Price, ssItem2Price, 1.325);
    SetCenterText(this->shopReturnText, ssReturn, 1.7);
    this->shopItemDefaultPrice.setPosition(this->shopItemDefaultPrice.getPosition().x - 350, this->shopItemDefaultPrice.getPosition().y);
    this->shopItem1Price.setPosition(this->shopItem1Price.getPosition().x, this->shopItem1Price.getPosition().y);
    this->shopItem2Price.setPosition(this->shopItem2Price.getPosition().x + 350, this->shopItem2Price.getPosition().y);

    this->shopItemDefault.setPosition((this->window->getSize().x / 2 - this->shopItemDefault.getSize().x / 2) - 350, this->window->getSize().y / 2 - this->shopItemDefault.getSize().y / 2);
    this->shopItem1.setPosition((this->window->getSize().x / 2 - this->shopItem1.getSize().x / 2), this->window->getSize().y / 2 - this->shopItem1.getSize().y / 2);
    this->shopItem2.setPosition((this->window->getSize().x / 2 - this->shopItem2.getSize().x / 2) + 350, this->window->getSize().y / 2 - this->shopItem2.getSize().y / 2);

    sf::Sprite background(this->inGameTexture);
    float a = (float) this->window->getSize().x/(float) this->inGameTexture.getSize().x;
    float b = (float) this->window->getSize().y/(float) this->inGameTexture.getSize().y;
    background.scale(a, b);
    target.draw(background);

    target.draw(this->shopText);
    target.draw(this->coinsText);
    target.draw(this->playerSelectText);
    target.draw(this->shopItemDefault);
    target.draw(this->shopItem1);
    target.draw(this->shopItem2);
    target.draw(this->shopItemDefaultPrice);
    target.draw(this->shopItem1Price);
    target.draw(this->shopItem2Price);
    target.draw(this->shopReturnText);
    SetActivePlayerText(*this->window);
}

void Universe::InGame(sf::RenderTarget &target) {
    sf::Sprite background(this->inGameTexture);
    float a = (float) this->window->getSize().x/(float) this->inGameTexture.getSize().x;
    float b = (float) this->window->getSize().y/(float) this->inGameTexture.getSize().y;
    background.scale(a, b);

    target.draw(background);
    this->player->DrawTo(this->window);
    this->DrawObstacles();
    target.draw(this->uiText);
}

void Universe::PausedScreen(sf::RenderTarget& target)
{
    std::stringstream ss;

    ss << "Paused";

    SetCenterText(this->pausedText, ss, 1);

    target.draw(this->pausedText);
}

void Universe::EndScreen(sf::RenderTarget& target)
{
    std::stringstream ssTop;
    std::stringstream ssMiddle;
    std::stringstream ssBottom;

    ssTop << "No More Wishes";
    ssMiddle << "Wishes: " << this->score;
    ssBottom << "Press Backspace To Return To Main Menu";

    SetCenterText(this->endTextTop, ssTop, 0.4);
    SetCenterText(this->endTextMiddle, ssMiddle, 1);
    SetCenterText(this->endTextBottom, ssBottom, 1.6);

    sf::Sprite background(this->endTexture);
    float a = (float) this->window->getSize().x/(float) this->endTexture.getSize().x;
    float b = (float) this->window->getSize().y/(float) this->endTexture.getSize().y;
    background.scale(a, b);
    target.draw(background);

    target.draw(this->endTextTop);
    target.draw(this->endTextMiddle);
    target.draw(this->endTextBottom);
}

// Set Active Player Text
void Universe::SetActivePlayerText(sf::RenderTarget &target)
{
    std::stringstream ssActivePlayer;
    ssActivePlayer << "X";

    this->activePlayerText.setString(ssActivePlayer.str());
    SetCenterText(this->activePlayerText, ssActivePlayer, 1.05);

    switch (this->activePlayer)
    {
        case 0:
            this->activePlayerText.setPosition(this->activePlayerText.getPosition().x - 350, this->activePlayerText.getPosition().y);
            break;
        case 1:
            break;
        case 2:
            this->activePlayerText.setPosition(this->activePlayerText.getPosition().x + 350, this->activePlayerText.getPosition().y);
            break;
    }

    target.draw(this->activePlayerText);
}

// Spawn Displayables
void Universe::SpawnPlayer() {
    this->player->SetSpeed(400);
    this->player->SetSize(80, 50);
    this->player->SetPos({float(this->width / 2) - (this->player->GetSize().GetX() / 2), float(this->height) - 55});
}

void Universe::SpawnObstacles() {
    int randomDirection = rand() % 2;
    int randomSpeedX = (rand() % 25) + 50;
    int randomSpeedY = (rand() % 25) + 150;
    if (randomDirection == 1)
        this->obstacle.SetSpeed(randomSpeedX, randomSpeedY);
    else
        this->obstacle.SetSpeed(-randomSpeedX, randomSpeedY);

    int type = rand() % 5;

    this->obstacle.SetType(type);

    rand() % (this->width - int(this->obstacle.GetSize().GetX()));
    float randomFloat = rand() % (this->width - int(this->obstacle.GetSize().GetX()));

    if (randomFloat <= this->obstacle.GetSize().GetX() / 1.5f)
    {
        randomFloat += this->obstacle.GetSize().GetX();
    }

    this->obstacle.SetPos({(randomFloat - this->obstacle.GetSize().GetX()), 0});

    this->obstacles.push_back(this->obstacle);
}

// Update Displayables
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

        this->obstacles[i].Move(this->deltaTime->GetDT());

        // Check For Collision
        bool collisionX = this->player->GetPos().GetX() + this->player->GetSize().GetX() >= this->obstacles[i].GetPos().GetX() &&
                this->obstacles[i].GetPos().GetX() + this->obstacles[i].GetSize().GetX() >= this->player->GetPos().GetX();

        bool collisionY = this->player->GetPos().GetY() + this->player->GetSize().GetY() >= this->obstacles[i].GetPos().GetY() &&
                this->obstacles[i].GetPos().GetY() + this->obstacles[i].GetSize().GetY() >= this->player->GetPos().GetY();

        if (collisionX && collisionY)
        {
            dead = true;

            this->obstacles[i].DoesDealDamage() ? this->soundManager->PlayNegative() : this->soundManager->PlayPositive();
            this->obstacles[i].DoesDealDamage() ? this->health -= this->obstacles[i].GetDamagePoints() : this->score += this->obstacles[i].GetScorePoints();
        }

        if (this->obstacles[i].IsNotCatched(this->height))
        {
            dead = true;
        }

        if (dead)
        {
            this->obstacles.erase(this->obstacles.begin() + i);
        }

        this->obstacles[i].IsCollidingWithBounds(this->width);
    }
}

void Universe::UpdateText() {
    std::stringstream ss;

    ss << "Wishes: " << this->score << "\n" << "Misfortune: " << this->health << "\n" << "P - Pause" << "\n" << "Backspace - Return" << "\n";

    this->uiText.setString(ss.str());
}

void Universe::SetCenterText(sf::Text& _text, std::stringstream& _stream, float _offSet)
{
    _text.setString(_stream.str());

    sf::FloatRect textRect = _text.getLocalBounds();
    _text.setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top + textRect.height/2.0f);
    _text.setPosition(sf::Vector2f(this->width/2.0f, this->height/2.0f * _offSet));
}

// Check For Inputs (Seperate From Movement)
void Universe::PollEvents() {
    if (this->window->pollEvent(this->ev)) {
        if (this->ev.type == sf::Event::Closed)
        {
            this->window->close();
        }
        if (this->ev.type == sf::Event::KeyPressed)
        {
            // Pause Game
            if (this->ev.key.code == sf::Keyboard::P && this->hasBegan && !this->endGame)
                this->paused = !this->paused;

            // Select/Purchase Player
            if (this->ev.key.code == sf::Keyboard::Num1 && !this->hasBegan && !this->endGame && this->hasShopOpen)
            {
                this->activePlayer = 0;
                this->shop->SetActivePlayer(0);
                this->player->SetTexture(this->activePlayer);
            }
            if (this->ev.key.code == sf::Keyboard::Num2 && !this->hasBegan && !this->endGame && this->hasShopOpen)
            {
                if (this->shop->isBoughtPlayer(1))
                {
                    this->activePlayer = 1;
                    this->shop->SetActivePlayer(1);
                    this->player->SetTexture(this->activePlayer);
                }
                else if (this->coins >= 500)
                {
                    this->activePlayer = 1;
                    this->shop->BuyPlayer(1);
                    this->shop->SetActivePlayer(1);
                    this->player->SetTexture(this->activePlayer);
                    this->shop->UpdateCoins(-500);
                    this->coins = this->shop->GetCoins();
                }
            }
            if (this->ev.key.code == sf::Keyboard::Num3 && !this->hasBegan && !this->endGame && this->hasShopOpen)
            {
                if (this->shop->isBoughtPlayer(2))
                {
                    this->activePlayer = 2;
                    this->shop->SetActivePlayer(2);
                    this->player->SetTexture(this->activePlayer);
                }
                else if (this->coins >= 1000)
                {
                    this->activePlayer = 2;
                    this->shop->BuyPlayer(2);
                    this->shop->SetActivePlayer(2);
                    this->player->SetTexture(this->activePlayer);
                    this->shop->UpdateCoins(-1000);
                    this->coins = this->shop->GetCoins();
                }
            }
        }
    }

    // On Close
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->window->close();
    }
    // Start Game
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !this->hasBegan && !this->endGame && !this->hasShopOpen)
    {
        this->hasBegan = true;
    }
    // Open Shop
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !this->hasBegan && !this->endGame && !this->hasShopOpen)
    {
        this->hasShopOpen = true;
    }
    // Close Shop
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && !this->hasBegan && !this->endGame && this->hasShopOpen)
    {
        this->hasShopOpen = false;
    }
    // Return To Main Menu (When Playing)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && this->hasBegan && !this->endGame)
    {
        ResetGame();
        this->hasBegan = false;
    }
    // Return To Main Menu (After Death)
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && this->endGame)
    {
        ResetGame();
    }
}

// Update Everything
void Universe::Update() {
    this->PollEvents();

    this->deltaTime->UpdateDT();

    if (!this->endGame && this->hasBegan && !this->paused)
    {
        this->player->Move(this->deltaTime->GetDT());
        this->UpdateObstacles();
        this->UpdateText();
    }

    if (this->health <= 0 && !this->endGame)
    {
        this->shop->UpdateCoins(this->score);
        this->coins = this->shop->GetCoins();
        this->endGame = true;
        this->paused = false;
    }
}

// Bool States
bool Universe::Running() const {
    return this->window->isOpen();
}

bool Universe::GetEndGame() const {
    return this->endGame;
}

// Reset
void Universe::ResetGame() {
    this->player->ResetPlayer();
    SpawnPlayer();
    this->InitVariables(this->width, this->height);

    for (int i = 0; i < this->obstacles.size(); i++) {
        this->obstacles.erase(this->obstacles.begin() + i);
    }

    this->obstacles.clear();
}

// Draw Everything
void Universe::DrawObstacles() {
    for (auto &e : this->obstacles)
    {
        e.DrawTo(this->window);
    }
}

void Universe::Draw()
{
    this->window->clear();

    if (!this->hasBegan && !this->hasShopOpen)
    {
        BeginScreen(*this->window);
    }
    else if (this->hasShopOpen)
    {
        ShopScreen(*this->window);
    }
    else if (this->endGame)
    {
        EndScreen(*this->window);
    }
    else
    {
        InGame(*this->window);

        if (this->paused)
            PausedScreen(*this->window);
    }

    this->window->display();
}