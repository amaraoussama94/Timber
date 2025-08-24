/**
 * @file Player.hpp
 * @brief Declaration of the Player class for managing player attributes and actions.
 * @details This class encapsulates the player's sprite, position, and side (left or right).
 * It provides methods to initialize the player, move the player to a specified side,
 * and hide the player off-screen.
 * @author Oussama Amara
 * @date 2025-08-15
 */
#pragma once
#include <SFML/Graphics.hpp>

enum class side { LEFT, RIGHT, NONE };

class Player {
public:
    sf::Sprite sprite;
    side playerSide;

    void init(const sf::Vector2f& resolution);
    void moveTo(side newSide, const sf::Vector2f& resolution);
    void hide();
};
