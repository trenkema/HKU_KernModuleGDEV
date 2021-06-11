#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#define velThing 2.71828

class Obstacle {
public:
    Obstacle()
    {
        this->frictionCoef = 0.6;
        this->mass = 1;
        this->velocityX = 0;
        this->velocityY = 0;
        this->textureNormal.loadFromFile("../Images/NormalStar.png");
        this->textureSuper.loadFromFile("../Images/SuperStar.png");
        this->textureHappy.loadFromFile("../Images/HappyStar.png");
        this->textureEnemy.loadFromFile("../Images/EnemyStar.png");
    }

    void SetSpeed(float _speedX, float _speedY)
    {
        this->speedX = _speedX;
        this->speedY = _speedY;
    }

    void SetSize(float _sizeX, float _sizeY)
    {
        this->sizeX = _sizeX;
        this->sizeY = _sizeY;
        this->obstacle.setSize(sf::Vector2f(this->sizeX, this->sizeY));
    }

    void DrawTo(sf::RenderWindow *window)
    {
        window->draw(this->obstacle);
    }

    void Move(float dt)
    {
        // Acceleration Physics Van Wridzer
        float accelerationX = 0;
        float accelerationY = 0;

        accelerationX += (this->speedX * dt);
        accelerationY += (this->speedY * dt);

        this->velocityX = (1/this->frictionCoef) * (std::pow(velThing,-this->frictionCoef/this->mass*dt))*(this->frictionCoef*this->velocityX+this->mass*accelerationX)-(this->mass*accelerationX/this->frictionCoef);
        this->velocityY = (1/this->frictionCoef) * (std::pow(velThing,-this->frictionCoef/this->mass*dt))*(this->frictionCoef*this->velocityY+this->mass*accelerationY)-(this->mass*accelerationY/this->frictionCoef);

        this->position += Vector2(this->velocityX, -this->velocityY);
        this->obstacle.setPosition(sf::Vector2f(this->position.GetX(), this->position.GetY()));
    }

    void SetPos(const Vector2& newPos)
    {
        this->position = newPos;
        this->obstacle.setPosition(sf::Vector2f(this->position.GetX(), this->position.GetY()));
    }

    int GetScorePoints() const
    {
        return this->scorePoints;
    }

    int GetDamagePoints() const
    {
        return this->damagePoints;
    }

    bool DoesDealDamage() const
    {
        return this->dealDamage;
    }

    void SetType(int _typeID)
    {
        this->typeID = _typeID;

        switch (_typeID)
        {
            case 0: // Normal Star
                this->dealDamage = false;
                this->scorePoints = 1;
                this->damagePoints = 0;
                SetSize(40, 40);
                this->obstacle.setTexture(&this->textureNormal);
                break;
            case 1: // Super Star
                this->dealDamage = false;
                this->scorePoints = 3;
                this->damagePoints = 0;
                SetSize(25, 25);
                this->obstacle.setTexture(&this->textureSuper);
                break;
            case 2: // Enemy Star
                this->dealDamage = true;
                this->scorePoints = 0;
                this->damagePoints = 1;
                SetSize(40, 40);
                this->obstacle.setTexture(&this->textureEnemy);
                break;
            case 3: // Enemy Star
                this->dealDamage = true;
                this->scorePoints = 0;
                this->damagePoints = 1;
                SetSize(30, 30);
                this->obstacle.setTexture(&this->textureEnemy);
                break;
            case 4: // Happy Star
                this->dealDamage = false;
                this->scorePoints = 2;
                this->damagePoints = 0;
                SetSize(30, 30);
                this->obstacle.setTexture(&this->textureHappy);
                break;
        }
    }

    void IsCollidingWithBounds(int maxBoundary)
    {
        if (this->position.GetX() < 0 || this->position.GetX() + this->sizeX  > maxBoundary)
        {
            this->velocityX *= -1;
            this->speedX *= -1;
        }
    }

    bool IsNotCatched(int maxBoundary)
    {
        if (this->position.GetY() + this->sizeY > maxBoundary)
        {
            return true;
        }
        return false;
    }

    Vector2 GetPos()
    {
        return this->position;
    }

    Vector2 GetSize() const
    {
        return Vector2(this->sizeX, this->sizeY);
    }

private:
    float velocityX;
    float velocityY;
    float frictionCoef;
    float mass;
    float speedX, speedY;
    float sizeX, sizeY;

    Vector2 position;

    sf::Texture textureNormal;
    sf::Texture textureSuper;
    sf::Texture textureHappy;
    sf::Texture textureEnemy;

    sf::RectangleShape obstacle;

    int typeID;
    bool dealDamage;
    int scorePoints;
    int damagePoints;
};
