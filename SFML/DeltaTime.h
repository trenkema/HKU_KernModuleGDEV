#pragma once
#include <SFML/Graphics.hpp>

class DeltaTime {
public:
    DeltaTime();
    ~DeltaTime();

    float GetDT() const;
    void UpdateDT();
private:
    sf::Clock clock;

    float dt;
};