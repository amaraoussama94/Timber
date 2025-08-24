/**
 * @file UI.hpp
 * @brief User Interface management for the Timber!!! game.
 * This file contains the declaration of the UI class, which handles
 * displaying score, time bar, messages, and FPS in the game window.
 * It uses SFML for rendering text and shapes.
 * @version 1.0
 * @date 2024-08-15
 * @author Oussama Amara
 */
#pragma once
#include <SFML/Graphics.hpp>

class UI {
public:
    sf::Text messageText, scoreText, FPSText;
    sf::Font font;
    sf::RectangleShape timeBar;
    sf::Text highScoreText;


    void init(const sf::Vector2f& resolution);
    void draw(sf::RenderWindow& window);

    void updateScore(int score);
    void updateFPS(float fps);
    void updateTimeBar(float timeRemaining, float timeBarWidthPerSecond);
    void showMessage(const std::string& message, const sf::Vector2f& resolution);
    void updateHighScore(int highScore) ;
};
