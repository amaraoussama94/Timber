#pragma once
#include <SFML/Audio.hpp>

class SoundManager {
public:
    sf::Sound chop, death, outOfTime;

    void init();
};
