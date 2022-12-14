// Include important libraries here
#include <SFML/Graphics.hpp>
#include <sstream>///for  string 
#include <SFML/Audio.hpp>
// Make code easier to type with "using namespace"
using namespace sf;
// Function declaration
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
const int NUM_TREE = 6;
Sprite branches[NUM_BRANCHES];
// Where is the player/branch?
// Left or Right
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];
// This is where our game starts from
int main()
{

    // Get the screen resolution and create an SFML window and View
	
    // Create a video mode object
   // VideoMode vm(1024,768);//resolution // 1366x 768//1280x720//1024x768//800x600
   // Create and open a window for the game
   // RenderWindow window(vm,"Timber!!!");//, Style::Fullscreen) for  full screen
    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
// Create and open a window for the game
// A regular RenderWindow
	RenderWindow window;
    window.create(VideoMode(resolution.x, resolution.y),"Timber!!!");//,Style::Fullscreen
   
// Create a texture to hold a graphic on the GPU
    Texture textureBackground;
// Load a graphic into the texture
    textureBackground.loadFromFile("graphics/background.png");//_1_1024x768 this  wase for my pc  resolution
// Create a sprite
    Sprite spriteBackground;
// Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);
// Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0,0);
// Make a tree sprite
   Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");//_1_150x700 also foor my pc dude stop reading
    Sprite spriteTree ;
    spriteTree.setTexture(textureTree); 
    spriteTree.setPosition((resolution.x /2.0)-180,0);//(400,0) guess what yes also for my pc 
    //Background Tree
     Texture textureBackTree;/*************************************************************************************************************/
    textureBackTree.loadFromFile("graphics/tree2.png");//back_tree_1_90x700 also this
    Sprite spriteBackTree[NUM_TREE];
    for(int i =1 ; i<NUM_TREE; i++)
    {   if((((resolution.x /2.0)-500)>(300*i)) && ((300*i)>((resolution.x /2.0)+500)))
            continue;
        spriteBackTree[i].setTexture(textureBackTree);
        spriteBackTree[i].setPosition(500*i,0);
    }
// Prepare the bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");//_50
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0,(resolution.y/2.0)+300);
// Is the bee currently moving?
    bool beeActive = false;
// How fast can the bee fly
    float beeSpeed = 0.0f;
// make 3 cloud sprites from 1 texture
    Texture textureCloud;
// Load 1 new texture
    textureCloud.loadFromFile("graphics/cloud.png"); //_50   
// 3 New sprites with the same texture
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
// Position the clouds on the left of the screen
// at different heights
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 100);
    spriteCloud3.setPosition(0, 200);
// Are the clouds currently on screen?
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
// How fast is each cloud?
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;
// Variables to control time itself
    Clock clock;
    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight =40;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((resolution.x  / 2) - timeBarStartWidth / 2, resolution.y- 150);
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
// Track whether the game is running
    bool paused = true;
// Draw some text
    int score = 0;
    float Last_time=0.0f;
    Text messageText;
    Text scoreText;
    Text FPSText;
// We need to choose a font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
// Set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);
    FPSText.setFont(font);
// Assign the actual message
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");
    FPSText.setString("FPS = 0");
// Make it really big
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(50);
    FPSText.setCharacterSize(50);
// Choose a color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);
    FPSText.setFillColor(Color::White);
// Position the text
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left +textRect.width / 2.0f,textRect.top +textRect.height / 2.0f);
    messageText.setPosition(resolution.x  / 2.0f, resolution.y  / 2.0f);
    scoreText.setPosition(20, 20);
    FPSText.setPosition(resolution.x -290, 20);
// Prepare 6 branches
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");//_50
// Set the texture for each branch sprite
    for (int i = 0; i < NUM_BRANCHES; i++) 
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-1000, -1000);
// Set the sprite's origin to dead centre
// We can then spin it round without changing its position
        branches[i].setOrigin(220, 40);//half of the size of image(110.10)
    }
// Prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");//_50
    Sprite spritePlayer; 
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition((resolution.x /2.0)+200 , resolution.y-370);// (590, 590)
// The player starts on the left
    side playerSide = side::LEFT;
// Prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition((resolution.x /2.0)+200 , resolution.y-320) ;// (590, 590)
// Prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition((resolution.x /2.0)+70, resolution.y-260);//(525, 613)
// Line the axe up with the tree
    const float AXE_POSITION_LEFT = (resolution.x /2.0)-270; 
    const float AXE_POSITION_RIGHT = (resolution.x /2.0)+70;
// Prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");//_2_150x70 for my pc also yap
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition((resolution.x /2.0)-180 ,resolution.y-300 );//   (245, 550)
// Some other useful log related variables
    bool logActive = false;
    float logSpeedX = 1000;//1000
    float logSpeedY = -1500;//-1500
// Control the player input
    bool acceptInput = false;
// Prepare the sounds
// The player chopping sound
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);
// The player has met his end under a branch
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);
// Out of time
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/time_out.flac");//time_out.flac//out_of_time.wav
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);
// const for FPS  calculation 
    int passetime =0;
while (window.isOpen())
    {
/*
****************************************
Handle the players input
****************************************
*/   
   Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::KeyReleased && !paused)
        {
// Listen for key presses again
            acceptInput = true;
// hide the axe
            spriteAxe.setPosition(2000,spriteAxe.getPosition().y);
        }
//normale  mode  close  the  game using the  button
        if (event.type == sf::Event::Closed)
                window.close();
    }


// press escape  key to close the game 
    if  (Keyboard::isKeyPressed(Keyboard::Escape)) 
        {
                window.close();
        }
// Start the game
    if (Keyboard::isKeyPressed(Keyboard::Return))
    {
    paused = false;
// Reset the time and the score
    score = 0;
    timeRemaining = 6;
// Make all the branches disappear -
// starting in the second position
    for (int i = 1; i < NUM_BRANCHES; i++)
        {
        branchPositions[i] = side::NONE;
        }
// Make sure the gravestone is hidden
    spriteRIP.setPosition(675, 2000);
// Move the player into position
    spritePlayer.setPosition((resolution.x /2.0)+200 , resolution.y-370);// 590, 560
    acceptInput = true;
    }
// Wrap the player controls to
// Make sure we are accepting input
    if (acceptInput)
        {
// First handle pressing the right cursor key
        if (Keyboard::isKeyPressed(Keyboard::Right))
            {
// Make sure the player is on the right
            playerSide = side::RIGHT;
            score ++;
// Add to the amount of time remaining
            timeRemaining += (2 / score) + .15;
            spriteAxe.setPosition(AXE_POSITION_RIGHT,spriteAxe.getPosition().y);
            spritePlayer.setPosition((resolution.x /2.0)+200 , resolution.y-370);/*****position to update*/// 590, 560
            //spritePlayer.setRotation(0);
// Update the branches
            updateBranches(score);
// Set the log flying to the left
            spriteLog.setPosition((resolution.x /2.0)-180 ,resolution.y-300 );//(245, 480)
            logSpeedX = -5000;//-5000
            logActive = true;
            acceptInput = false;
// Play a chop sound
            chop.play();
            }
// Handle the left cursor key
        if (Keyboard::isKeyPressed(Keyboard::Left))
            {
// Make sure the player is on the left
            playerSide = side::LEFT;
            score++;
// Add to the amount of time remaining
            timeRemaining += (2 / score) + .15;
            spriteAxe.setPosition(AXE_POSITION_LEFT,spriteAxe.getPosition().y);
            spritePlayer.setPosition((resolution.x /2.0)-400 , resolution.y-370);//(280, 560
            //spritePlayer.setRotation(270);
// update the branches
            updateBranches(score);
// set the log flying
            spriteLog.setPosition((resolution.x /2.0)-180 ,resolution.y-300 );//(300, 480)
            logSpeedX = 5000;//5000
            logActive = true;
            acceptInput = false;
// Play a chop sound
            chop.play();
            }
        }
    
   
/*
**************************************** 
Update the scene
****************************************
*/

    if (!paused)
    {
// Measure time:returns the amount of time that has elapsed since the last time we restarted the clock
        Time dt = clock.restart();
// Subtract from the amount of time remaining
    timeRemaining -= dt.asSeconds(); 
// size up the time bar
    
    timeBar.setSize(Vector2f(timeBarWidthPerSecond *timeRemaining, timeBarHeight));
    //FPS  calculation
     passetime += dt.asMilliseconds();
    if(passetime > 80) //to make FPS  visibale for reader mae it 100<x<1000
    {
        float FPS= 1.0f /dt.asSeconds() ;
        // create  string  object 
        std::stringstream sFPS;
        //create  the  string  with actual result  to print it n the  screen
        sFPS<< "FPS = " << FPS;
        // update the  screen with the new  FPS
        FPSText.setString(sFPS.str());
       passetime =0;
    }
    if (timeRemaining<= 0.0f) 
    {
// Pause the game
        paused = true;
// Change the message shown to the player
        messageText.setString("Out of time!!");
//Reposition the text based on its new size
        FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left +textRect.width / 2.0f,textRect.top +textRect.height / 2.0f);
        messageText.setPosition(1080 / 2.0f, 768 / 2.0f);
// Play the out of time sound
        outOfTime.play();
    }
// Setup the bee
        if (!beeActive)
        {
// How fast is the bee
        srand((int)time(0));
        beeSpeed = (rand() % 200) + 200;
// How high is the bee
        srand((int)time(0) * 10);
        float height = (rand() % 370) + 384;
        spriteBee.setPosition(1100, height);
        beeActive = true;
        }
        else
// Move the bee
        {
        spriteBee.setPosition(spriteBee.getPosition().x -(beeSpeed * dt.asSeconds()),spriteBee.getPosition().y);
// Has the bee reached the left-hand edge of the screen?
        if (spriteBee.getPosition().x < -100)
            {
// Set it up ready to be a whole new bee next frame
            beeActive = false;
            }
        }
// Manage the clouds
// Cloud 1
        if (!cloud1Active)
        {
// How fast is the cloud
        srand((int)time(0) * 10);
        cloud1Speed = (rand() % 200);
// How high is the cloud
        srand((int)time(0) * 10);
        float height = (rand() % 100);
        spriteCloud1.setPosition(-200, height);
        cloud1Active = true;
        }
        else
        {
        spriteCloud1.setPosition(spriteCloud1.getPosition().x +(cloud1Speed * dt.asSeconds()),spriteCloud1.getPosition().y);
 // Has the cloud reached the right hand edge of the screen?
        if (spriteCloud1.getPosition().x > 1080)
            {
// Set it up ready to be a whole new cloud next frame
            cloud1Active = false;
            }
        }
// Cloud 2
        if (!cloud2Active)
        {
// How fast is the cloud
        srand((int)time(0) * 20);
        cloud2Speed = (rand() % 200);
// How high is the cloud
        srand((int)time(0) * 20);
        float height = (rand() % 200) -50;
        spriteCloud2.setPosition(-200, height);
        cloud2Active = true;
        }
        else
        {
        spriteCloud2.setPosition(spriteCloud2.getPosition().x +(cloud2Speed * dt.asSeconds()),spriteCloud2.getPosition().y);
// Has the cloud reached the right hand edge of the screen?
        if (spriteCloud2.getPosition().x > 1080)
            { 
// Set it up ready to be a whole new cloud next frame
            cloud2Active = false;
            }
        }
// Cloud 3
        if (!cloud3Active)
        {
// How fast is the cloud
        srand((int)time(0) * 30);
        cloud3Speed = (rand() % 200);
// How high is the cloud
        srand((int)time(0) * 30);
        float height = (rand() % 300) - 50;
        spriteCloud3.setPosition(-200, height);
        cloud3Active = true;
        }
        else
        {
        spriteCloud3.setPosition(spriteCloud3.getPosition().x +(cloud3Speed * dt.asSeconds()),spriteCloud3.getPosition().y);
// Has the cloud reached the right hand edge of the screen?
        if (spriteCloud3.getPosition().x > 1080)
            {
// Set it up ready to be a whole new cloud next frame
            cloud3Active = false;
            }
        }
// Update the score text
        std::stringstream ss;
        ss<< "Score = " << score;
        scoreText.setString(ss.str());
// update the branch sprites
    for (int i = 0; i < NUM_BRANCHES; i++)
        {
        float height = i * 150;
        // if  we  reach end off tree don't move  the  branch make it  desspare
        if (height>650)
            continue;
        if (branchPositions[i] == side::LEFT)
            {
            // Move the sprite to the left side
            branches[i].setPosition((resolution.x /2.0)-380, height);// 290
            // Flip the sprite round the other way
            branches[i].setRotation(190);
            }
        else if (branchPositions[i] == side::RIGHT)
            {
            // Move the sprite to the right side*
            branches[i].setPosition((resolution.x /2.0)+320 , height);//650
            // Set the sprite rotation to normal
            branches[i].setRotation(0);
            }
        else
            {
            // Hide the branch
            branches[i].setPosition(3000, height);
            }
            // Handle a flying log
        if (logActive)
        {
            spriteLog.setPosition(spriteLog.getPosition().x +(logSpeedX * dt.asSeconds()), spriteLog.getPosition().y +(logSpeedY * dt.asSeconds()));
            // Has the log reached the right hand edge?
            if (spriteLog.getPosition().x < -100 ||spriteLog.getPosition().x > 2000)
            {
                // Set it up ready to be a whole new log next frame// log  that will be  moving  
                logActive = false;
                spriteLog.setPosition((resolution.x /2.0)-180 ,resolution.y-300 );
            }
        }
        // has the player been squished by a branch?
        if (branchPositions[5] == playerSide)
        {
            // death
            paused = true;
            acceptInput = false;
            if(branchPositions[5] == side::LEFT)
            {
                // Draw the gravestone
                spriteRIP.setPosition((resolution.x /2.0)-400 , resolution.y-320) ;//(280, 590)
                spriteLog.setPosition(2000, 550);//make them disapare from thr screen
                spriteAxe.setPosition(2000,spriteAxe.getPosition().y);
            } 
            if(branchPositions[5] == side::RIGHT)
            {
                // Draw the gravestone
                spriteRIP.setPosition((resolution.x /2.0)+200 , resolution.y-320);//(590, 590)
                spriteLog.setPosition(2000, 550);
                spriteAxe.setPosition(2000,spriteAxe.getPosition().y);
            }
            // hide the player
            spritePlayer.setPosition(2000, 660);
            // Change the text of the message
            messageText.setString("SQUISHED!!");
            // Center it on the screen
            FloatRect textRect = messageText.getLocalBounds();
            messageText.setOrigin(textRect.left +textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);
            messageText.setPosition(resolution.x /2.0f,resolution.y/2.0f);// (1080 / 2.0f,768 / 2.0f)
            // Play the death sound
            death.play();
            }
       } 
    } // End if(!paused)


/*
****************************************
Draw the scene
****************************************
*/
// Clear everything from the last frame
    window.clear();
// Draw our game scene here
    window.draw(spriteBackground);
// Draw the clouds
    window.draw(spriteCloud1);
    window.draw(spriteCloud2);
    window.draw(spriteCloud3);
    for(int i =1;i<NUM_TREE;i++)
    {
        window.draw(spriteBackTree[i]);/*************************************************************************************************************/
    } 
// Draw the branches
    for (int i = 0; i < NUM_BRANCHES; i++) 
    {
        window.draw(branches[i]);
    }
// Draw the tree
    window.draw(spriteTree);
// Draw the player
    window.draw(spritePlayer);
// Draw the axe
    window.draw(spriteAxe);
// Draw the flying log
    window.draw(spriteLog);
// Draw the gravestone
    window.draw(spriteRIP);
// Draw the bee
// Draw the insect
    window.draw(spriteBee);
// Draw the score
    window.draw(scoreText);
// Draw the timebar
    window.draw(timeBar);
// Draw the FPS
    window.draw(FPSText);
    if (paused)
    {
// Draw our message
        window.draw(messageText);
    }
// Show everything we just drew
    window.display();
    }
return 0;
}

// Function definition
void updateBranches(int seed)
{
    // Move all the branches down one place
    for (int j = NUM_BRANCHES-1; j > 0; j--) 
    {
        branchPositions[j] = branchPositions[j - 1];
    }
// Spawn a new branch at position 0
// LEFT, RIGHT or NONE
    srand((int)time(0)+seed);
    int r = (rand() % 5);
    switch (r) 
    {
        case 0:branchPositions[0] = side::LEFT;
            break;
        case 1:branchPositions[0] = side::RIGHT;
            break;
        default:branchPositions[0] = side::NONE;
            break;
    }
}
