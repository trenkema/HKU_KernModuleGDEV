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
    Player()
    {
        texture.loadFromFile("../Player.png");
        player.setTexture(&texture);
    }

    void setSpeed(float speedX)
    {
        this->speedX = speedX;
    }

    void setSize(float _sizeX, float _sizeY)
    {
        this->sizeX = _sizeX;
        this->sizeY = _sizeY;
        player.setSize(sf::Vector2f(this->sizeX, this->sizeY));
    }

    void drawTo(sf::RenderWindow *window)
    {
        sf::Sprite _player(this->texture);
        window->draw(player);
    }

    void move()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed((sf::Keyboard::A)))
        {
            position -= Vector2(speedX, 0);
            player.setPosition(sf::Vector2f(position.GetX(), position.GetY()));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed((sf::Keyboard::D)))
        {
            position += Vector2(speedX, 0);
            player.setPosition(sf::Vector2f(position.GetX(), position.GetY()));
        }
    }

    void setPos(Vector2 newPos)
    {
        position = newPos;
        player.setPosition(sf::Vector2f(position.GetX(), position.GetY()));
    }

    bool isCollidingWithObstacle(Obstacle obstace)
    {
        if (player.getGlobalBounds().intersects(obstace.getBounds()))
        {
            return true;
        }
        return false;
    }

private:
    Vector2 position;
    sf::Texture texture;
    sf::RectangleShape player;
    float speedX;
    float sizeX, sizeY;
};
