//
// Created by tomre on 2-6-2021.
//
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include "Vector2.h"

class Player {
public:
    Player(int _boundX)
    {
        this->speedX = 0;
        this->sizeX = 0;
        this->sizeY = 0;
        this->velocity = 0;
        this->boundX = _boundX;
    }

    void SetTexture(int _playerID)
    {
        switch(_playerID)
        {
            case 0:
                this->texture.loadFromFile("../Images/Player.png");
                this->player.setTexture(&this->texture);
                break;
            case 1:
                this->texture.loadFromFile("../Images/Player1.png");
                this->player.setTexture(&this->texture);
                break;
            case 2:
                this->texture.loadFromFile("../Images/Player2.png");
                this->player.setTexture(&this->texture);
                break;
        }
    }

    void SetSpeed(float _speedX)
    {
        this->speedX = _speedX;
    }

    void SetSize(float _sizeX, float _sizeY)
    {
        this->sizeX = _sizeX;
        this->sizeY = _sizeY;
        this->player.setSize(sf::Vector2f(this->sizeX, this->sizeY));
    }

    void DrawTo(sf::RenderWindow *window)
    {
        window->draw(this->player);
    }

    void Move(float dt)
    {
        // Acceleration Physics Van Wridzer
        float acceleration = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed((sf::Keyboard::A)))
        {
            acceleration += this->speedX * dt;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed((sf::Keyboard::D)))
        {
            acceleration -= this->speedX * dt;
        }

        this->velocity = (1 / this->frictionCoef) * (std::pow(2.71828,-this->frictionCoef / this->mass * dt)) *
                (this->frictionCoef * this->velocity + this->mass * acceleration) - (this->mass * acceleration / this->frictionCoef);
        this->position += Vector2(this->velocity, 0);

        IsCollidingWithBounds(this->boundX);

        this->player.setPosition(sf::Vector2f(this->position.GetX(), this->position.GetY()));
    }

    void IsCollidingWithBounds(int maxBoundary)
    {
    if (this->position.GetX() < 0 - this->sizeX) {
        this->position += Vector2(maxBoundary, 0);
    }
    else if (this->position.GetX() > maxBoundary) {
        this->position += Vector2(-maxBoundary, 0);
    }
    }

    void SetPos(Vector2 newPos)
    {
        this->position = newPos;
        this->player.setPosition(sf::Vector2f(this->position.GetX(), this->position.GetY()));
    }

    Vector2 GetSize()
    {
        return Vector2(this->sizeX, this->sizeY);
    }

    Vector2 GetPos()
    {
        return this->position;
    }

    void ResetPlayer()
    {
        this->velocity = 0;
    }

private:
    int boundX;

    float speedX;
    float sizeX, sizeY;

    float velocity;
    float frictionCoef = 0.6;
    float mass = 1;

    Vector2 position;

    sf::Texture texture;

    sf::RectangleShape player;
};
