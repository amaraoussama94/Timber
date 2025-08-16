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

};
