/**
 * @file BranchManager.hpp
 * @brief Manages the branches in the Timber!!! game.
 * This class handles the initialization, updating, and rendering of branches.
 * It also checks for collisions between the player and branches.
 * @version 1.0
 * @date 2025-8-15
 * @author Oussama Amara
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class BranchManager {
public:
    static const int NUM_BRANCHES = 6;
    sf::Sprite branches[NUM_BRANCHES];
    side branchPositions[NUM_BRANCHES];

    void init();
    void updateBranches(int seed);
    void updateSprites(float resolutionX);
    bool checkCollision(const side& playerSide);
    void drawBranches(sf::RenderWindow& window, sf::Vector2f resolution);
private:
    sf::Texture branchTexture;

};
