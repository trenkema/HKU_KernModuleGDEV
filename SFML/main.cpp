#include <iostream>
#include <SFML/Audio.hpp>
#include "Universe.h"
using namespace std;

int main() {
    srand((unsigned)time(0));
    Universe universe(1280, 800);

    sf::Music music;
    music.setVolume(4);
    music.setLoop(true);
    if (!music.openFromFile("../Sounds/BGMusic.wav"))
        return -1; // error
    music.play();

    while (universe.Running())
    {
        universe.Update();

        universe.Draw();
    }

    music.stop();

    return 0;
}
