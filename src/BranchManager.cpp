#include "BranchManager.hpp"
#include <ctime>

void BranchManager::init() {
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile("graphics/branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(*texture);
        branches[i].setPosition(-1000, -1000);
        branches[i].setOrigin(220, 40);
        branchPositions[i] = side::NONE;
    }
}

void BranchManager::drawBranches(sf::RenderWindow& window, sf::Vector2f resolution) {
    for (int i = 0; i < NUM_BRANCHES; i++) {
        float height = i * 150;
        branches[i].setPosition(resolution.x / 2.0f, height);
        window.draw(branches[i]);
    }
}

void BranchManager::updateBranches(int seed) {
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
        branchPositions[j] = branchPositions[j - 1];

    srand((int)time(0) + seed);
    int r = rand() % 5;
    branchPositions[0] = (r == 0 ? side::LEFT : r == 1 ? side::RIGHT : side::NONE);
}

void BranchManager::updateSprites(float resolutionX) {
    for (int i = 0; i < NUM_BRANCHES; i++) {
        float height = i * 150;
        if (height > 650) continue;

        if (branchPositions[i] == side::LEFT) {
            branches[i].setPosition((resolutionX / 2.0f) - 380, height);
            branches[i].setRotation(190);
        } else if (branchPositions[i] == side::RIGHT) {
            branches[i].setPosition((resolutionX / 2.0f) + 320, height);
            branches[i].setRotation(0);
        } else {
            branches[i].setPosition(3000, height);
        }
    }
}

bool BranchManager::checkCollision(const side& playerSide) {
    return branchPositions[5] == playerSide;
}
