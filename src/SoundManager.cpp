#include "SoundManager.hpp"

void SoundManager::init() {
    sf::SoundBuffer* chopBuffer = new sf::SoundBuffer();
    sf::SoundBuffer* deathBuffer = new sf::SoundBuffer();
    sf::SoundBuffer* ootBuffer = new sf::SoundBuffer();

    chopBuffer->loadFromFile("sound/chop.wav");
    deathBuffer->loadFromFile("sound/death.wav");
    ootBuffer->loadFromFile("sound/time_out.flac");

    chop.setBuffer(*chopBuffer);
    death.setBuffer(*deathBuffer);
    outOfTime.setBuffer(*ootBuffer);
}
