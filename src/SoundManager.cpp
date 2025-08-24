/**
 * @file SoundManager.cpp
 * @brief Implementation of the SoundManager class for handling game sounds.
 * This class initializes and manages sound effects such as chopping, death, and out-of-time alerts.
 * It uses the SFML library for audio functionalities.
 * @version 1.0
 * @date 2025-08-15
 * @author Oussama Amara
 */
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
