/**
 * @file Player.cpp
 * @brief Implementation of the Player class for managing player character.
 * This includes initialization, movement, and hiding functionality.
 * The player can move between left and right sides of the screen.
 * @version 1.0
 * @date 2025-08-15
 * @author Oussama Amara
 */
#include "Player.hpp"

void Player::init(const sf::Vector2f& resolution) {
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile("graphics/player.png");
    sprite.setTexture(*texture);
    sprite.setPosition((resolution.x / 2.0f) + 200, resolution.y - 370);
    playerSide = side::LEFT;
}

void Player::moveTo(side newSide, const sf::Vector2f& resolution) {
    playerSide = newSide;
    if (newSide == side::LEFT)
        sprite.setPosition((resolution.x / 2.0f) - 400, resolution.y - 370);
    else
        sprite.setPosition((resolution.x / 2.0f) + 200, resolution.y - 370);
}

void Player::hide() {
    sprite.setPosition(2000, 660);
}
