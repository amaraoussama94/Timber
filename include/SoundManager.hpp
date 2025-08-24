/**
 * @file SoundManager.hpp
 * @brief Header file for the SoundManager class, which manages game sound effects.
 * This class provides an interface to initialize and play various sound effects used in the game.
 * It encapsulates SFML's sound functionalities to simplify sound management within the game.
 * The SoundManager class includes sound effects for chopping, player death, and running out of time.
 * It is designed to be easy to use and integrate into the game's main loop.
 * @version 1.0
 * @date 2025-08-15
 * @author Oussama Amara
 */
#pragma once
#include <SFML/Audio.hpp>

class SoundManager {
public:
    sf::Sound chop, death, outOfTime;

    void init();
private:
    sf::SoundBuffer chopBuffer;
    sf::SoundBuffer deathBuffer;
    sf::SoundBuffer outOfTimeBuffer;
};
