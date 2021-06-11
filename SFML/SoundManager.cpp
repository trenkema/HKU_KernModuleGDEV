#include "SoundManager.h"

SoundManager::SoundManager() {
    this->positiveBuffer.loadFromFile("../Sounds/Positive.wav");
    this->negativeBuffer.loadFromFile("../Sounds/Negative.wav");
}

SoundManager::~SoundManager() {};

void SoundManager::PlayPositive() {
    this->sound.setBuffer(this->positiveBuffer);
    this->sound.setVolume(40);
    this->sound.play();
}

void SoundManager::PlayNegative() {
    this->sound.setBuffer(this->negativeBuffer);
    this->sound.setVolume(100);
    this->sound.play();
}
