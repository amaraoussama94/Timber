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
