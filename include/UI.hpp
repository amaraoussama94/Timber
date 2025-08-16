#pragma once
#include <SFML/Graphics.hpp>

class UI {
public:
    sf::Text messageText, scoreText, FPSText;
    sf::Font font;
    sf::RectangleShape timeBar;

    void init(const sf::Vector2f& resolution);
    void draw(sf::RenderWindow& window);

    void updateScore(int score);
    void updateFPS(float fps);
    void updateTimeBar(float timeRemaining, float timeBarWidthPerSecond);
    void showMessage(const std::string& message, const sf::Vector2f& resolution);
};
