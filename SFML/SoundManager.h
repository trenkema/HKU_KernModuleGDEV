#pragma once
#include <SFML/Audio.hpp>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();
    void PlayPositive();
    void PlayNegative();
private:
    sf::SoundBuffer positiveBuffer;
    sf::SoundBuffer negativeBuffer;
    sf::Sound sound;
};