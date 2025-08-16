#include "UI.hpp"
#include <sstream>

void UI::init(const sf::Vector2f& resolution) {
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    messageText.setFont(font);
    scoreText.setFont(font);
    FPSText.setFont(font);

    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");
    FPSText.setString("FPS = 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(50);
    FPSText.setCharacterSize(50);

    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);
    FPSText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    messageText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);
    scoreText.setPosition(20, 20);
    FPSText.setPosition(resolution.x - 290, 20);

    timeBar.setSize(sf::Vector2f(400, 40));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition((resolution.x / 2.0f) - 200, resolution.y - 150);
}
void UI::draw(sf::RenderWindow& window) {
    window.draw(scoreText);
    window.draw(messageText);
    window.draw(timeBar);
    window.draw(FPSText);
}


void UI::updateScore(int score) {
    std::stringstream ss;
    ss << "Score = " << score;
    scoreText.setString(ss.str());
}

void UI::updateFPS(float fps) {
    std::stringstream sFPS;
    sFPS << "FPS = " << fps;
    FPSText.setString(sFPS.str());
}

void UI::updateTimeBar(float timeRemaining, float timeBarWidthPerSecond) {
    timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, 40));
}

void UI::showMessage(const std::string& message, const sf::Vector2f& resolution) {
    messageText.setString(message);
    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    messageText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);
}
