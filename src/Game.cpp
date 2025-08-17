#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <ctime>

// Include modular components
#include "Game.hpp"
#include "Player.hpp"
#include "BranchManager.hpp"
#include "SoundManager.hpp"
#include "UI.hpp"

void runGame() {
    using namespace sf;

    // === Setup resolution and window ===
    Vector2f resolution(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Timber!!!");

    // === Load background ===
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground(textureBackground);

    // === Load main tree and background trees ===
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree(textureTree);
    spriteTree.setPosition((resolution.x / 2.0f) - 180, 0);

    Texture textureBackTree;
    textureBackTree.loadFromFile("graphics/tree2.png");
    const int NUM_TREE = 6;
    Sprite spriteBackTree[NUM_TREE];
    for (int i = 1; i < NUM_TREE; i++) {
        spriteBackTree[i].setTexture(textureBackTree);
        spriteBackTree[i].setPosition(500 * i, 0);
    }

    // === Bee setup ===
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee(textureBee);
    spriteBee.setPosition(0, (resolution.y / 2.0f) + 300);
    bool beeActive = false;
    float beeSpeed = 0.0f;

    // === Cloud setup ===
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1(textureCloud), spriteCloud2(textureCloud), spriteCloud3(textureCloud);
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 100);
    spriteCloud3.setPosition(0, 200);
    bool cloud1Active = false, cloud2Active = false, cloud3Active = false;
    float cloud1Speed = 0.0f, cloud2Speed = 0.0f, cloud3Speed = 0.0f;

    // === Time and score tracking ===
    Clock clock;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = 400 / timeRemaining;
    int passetime = 0;
    int score = 0;

    // === Game state flags ===
    bool paused = true;
    bool acceptInput = false;

    // === Initialize modular systems ===
    Player player;
    player.init(resolution);

    BranchManager branchManager;
    branchManager.init();

    SoundManager soundManager;
    soundManager.init();

    UI ui;
    ui.init(resolution);

    // === RIP tombstone, axe, and log setup ===
    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP(textureRIP);
    spriteRIP.setPosition((resolution.x / 2.0f) + 200, resolution.y - 320);

    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition((resolution.x / 2.0f) + 70, resolution.y - 260);
    const float AXE_POSITION_LEFT = (resolution.x / 2.0f) - 270;
    const float AXE_POSITION_RIGHT = (resolution.x / 2.0f) + 70;

    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog(textureLog);
    spriteLog.setPosition((resolution.x / 2.0f) - 180, resolution.y - 300);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    // === Main game loop ===
    while (window.isOpen()) {
        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyReleased && !paused) {
                acceptInput = true;
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y); // Hide axe
            }
        }

        // Handle escape and restart
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            score = 0;
            timeRemaining = 6;
            for (int i = 1; i < BranchManager::NUM_BRANCHES; i++)
                branchManager.branchPositions[i] = side::NONE;
            spriteRIP.setPosition(675, 2000); // Hide RIP
            player.moveTo(side::LEFT, resolution);
            acceptInput = true;
        }

        // Handle player input
        if (acceptInput) {
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                player.moveTo(side::RIGHT, resolution);
                score++;
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                branchManager.updateBranches(score);
                spriteLog.setPosition((resolution.x / 2.0f) - 180, resolution.y - 300);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;
                soundManager.chop.play();
            } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                player.moveTo(side::LEFT, resolution);
                score++;
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                branchManager.updateBranches(score);
                spriteLog.setPosition((resolution.x / 2.0f) - 180, resolution.y - 300);
                logSpeedX = 5000;
                logActive = true;
                acceptInput = false;
                soundManager.chop.play();
            }
        }

        // === Game update logic ===
        if (!paused) {
            Time dt = clock.restart();
            timeRemaining -= dt.asSeconds();
            ui.updateTimeBar(timeRemaining, timeBarWidthPerSecond);

            passetime += dt.asMilliseconds();
            if (passetime > 80) {
                float FPS = 1.0f / dt.asSeconds();
                ui.updateFPS(FPS);
                passetime = 0;
            }

            if (timeRemaining <= 0.0f) {
                paused = true;
                ui.showMessage("Out of time!!", resolution);
                soundManager.outOfTime.play();
            }

            // Bee movement
            if (!beeActive) {
                beeSpeed = (rand() % 200) + 200;
                float height = (rand() % 370) + 384;
                spriteBee.setPosition(1100, height);
                beeActive = true;
            } else {
                spriteBee.move(-beeSpeed * dt.asSeconds(), 0);
                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            // Cloud movement logic
            auto cloudLogic = [&](Sprite& cloud, bool& active, float& speed, int heightRange) {
                if (!active) {
                    speed = (rand() % 200);
                    float height = (rand() % heightRange) - 50;
                    cloud.setPosition(-200, height);
                    active = true;
                } else {
                    cloud.move(speed * dt.asSeconds(), 0);
                    if (cloud.getPosition().x > resolution.x)
                        active = false;
                }
            };

            cloudLogic(spriteCloud1, cloud1Active, cloud1Speed, 100);
            cloudLogic(spriteCloud2, cloud2Active, cloud2Speed, 200);
            cloudLogic(spriteCloud3, cloud3Active, cloud3Speed, 300);

            ui.updateScore(score);
            branchManager.updateSprites(resolution.x);

            // Log movement
            if (logActive) {
                spriteLog.move(logSpeedX * dt.asSeconds(), logSpeedY * dt.asSeconds());
                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > resolution.x + 100)
                    logActive = false;
            }

            // Collision detection
            if (branchManager.checkCollision(player.playerSide)) {
                paused = true;
                acceptInput = false;
                player.sprite.setPosition(3000, resolution.y); // or use player.hide()
                spriteRIP.setPosition(
                    player.playerSide == side::LEFT ?
                    (resolution.x / 2.0f) - 400 :
                    (resolution.x / 2.0f) + 200,
                    resolution.y - 320
                );
                spriteLog.setPosition(2000, 550);
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
                ui.showMessage("SQUISHED!!", resolution);
                soundManager.death.play();
            }
        }

                // === Draw everything ===
        window.clear();

        // Draw background and decorative trees
        window.draw(spriteBackground);
        for (int i = 1; i < NUM_TREE; i++) {
            window.draw(spriteBackTree[i]);
        }

        // Draw dynamic elements
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteBee);
        window.draw(spriteTree);

        // Draw branches managed by BranchManager
        branchManager.drawBranches(window, resolution);

        // Draw RIP tombstone if player is squished
        window.draw(spriteRIP);

        // Draw player sprite
        window.draw(player.sprite);

        // Draw axe and log
        window.draw(spriteAxe);
        window.draw(spriteLog);

        // Draw UI elements (score, time bar, messages)
        ui.draw(window);

        // Display everything on screen
        window.display();
    }
}

