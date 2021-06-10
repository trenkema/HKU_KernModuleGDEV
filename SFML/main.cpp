#include <iostream>
#include <SFML/Audio.hpp>
#include "Universe.h"
using namespace std;

int main() {
    srand((unsigned)time(0));
    Universe universe(1280, 800);

    sf::Music music;
    if (!music.openFromFile("../BGMusic.wav"))
        return -1; // error
    music.play();
    music.setVolume(3);
    music.setLoop(true);

    while (universe.Running())
    {
        universe.Update();

        universe.Draw();
    }

    music.stop();

    return 0;
}
