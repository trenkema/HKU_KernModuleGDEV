#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Obstacle {
public:
    Obstacle()
    {
    }

    void setSpeed(float speedX, float speedY)
    {
        this->speedX = speedX;
        this->speedY = speedY;
    }

    void setSize(float _sizeX, float _sizeY)
    {
        this->sizeX = _sizeX;
        this->sizeY = _sizeY;
        this->obstacle.setSize(sf::Vector2f(this->sizeX, this->sizeY));
    }

    sf::Vector2f getSize()
    {
        return sf::Vector2f(this->sizeX, this->sizeY);
    }

    void drawTo(sf::RenderWindow *window)
    {
        this->texture.loadFromFile("../Star.png");
        this->obstacle.setTexture(&texture);
        window->draw(this->obstacle);
    }

    void move()
    {
        this->position += Vector2(this->speedX, this->speedY);
        this->obstacle.setPosition(sf::Vector2f(this->position.GetX(), this->position.GetY()));
    }

    void setPos(Vector2 newPos)
    {
        this->position = newPos;
        this->obstacle.setPosition(sf::Vector2f(this->position.GetX(), this->position.GetY()));
    }

    int GetScorePoints()
    {
        return this->scorePoints;
    }

    int GetDamagePoints()
    {
        return this->damagePoints;
    }

    sf::RectangleShape GetObstacle()
    {
        return this->obstacle;
    }

    int GetTypeID()
    {
        return this->typeID;
    }

    bool DoesDealDamage()
    {
        return dealDamage;
    }

    void SetType(int typeID)
    {
        this->typeID = typeID;

        switch (typeID)
        {
            case 0: // Normal Star
                dealDamage = false;
                this->scorePoints = 1;
                this->damagePoints = 1;
                setSize(40, 40);
                break;
            case 1: // Super Star
                dealDamage = false;
                this->scorePoints = 3;
                this->damagePoints = 1;
                setSize(25, 25);
                break;
            case 2: // Enemy Star
                dealDamage = true;
                this->scorePoints = -2;
                this->damagePoints = 1;
                setSize(40, 40);
                break;
            case 3: // Enemy Star
                dealDamage = true;
                this->scorePoints = -2;
                this->damagePoints = 1;
                setSize(40, 40);
                break;
        }
    }

    sf::FloatRect getBounds()
    {
        return this->obstacle.getGlobalBounds();
    }

    void isCollidingWithBounds(int maxBoundary)
    {
        if (this->position.GetX() < 0 || this->position.GetX() + this->sizeX  > maxBoundary)
        {
            this->speedX *= -1;
        }
    }

    bool isNotCatched(int maxBoundary)
    {
        if (this->position.GetY() + this->sizeY > maxBoundary)
        {
            return true;
        }
        return false;
    }

private:
    int scorePoints;
    int damagePoints;
    Vector2 position;
    sf::Texture texture;
    sf::RectangleShape obstacle;
    float speedX, speedY;
    float sizeX, sizeY;
    int typeID;
    bool dealDamage;
};
