// Include important libraries here
#include <SFML/Graphics.hpp>
// Make code easier to type with "using namespace"
using namespace sf;
// This is where our game starts from
int main()
{
// Create a video mode object
    VideoMode vm(1024,768);//resolution // 1366x 768//1280x720//1024x768//800x600
// Create and open a window for the game
    RenderWindow window(vm,"Timber!!!");//, Style::Fullscreen) for  full screen
// Create a texture to hold a graphic on the GPU
    Texture textureBackground;
// Load a graphic into the texture
    textureBackground.loadFromFile("graphics/background_1_1024x768.png");
// Create a sprite
    Sprite spriteBackground;
// Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);
// Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0,0);
// Make a tree sprite
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree_1_150x650.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(400,0);

// Prepare the bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee_50.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0,475);
// Is the bee currently moving?
    bool beeActive = false;
// How fast can the bee fly
    float beeSpeed = 0.0f;
// make 3 cloud sprites from 1 texture
    Texture textureCloud;
// Load 1 new texture
    textureCloud.loadFromFile("graphics/cloud_50.png");
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
    while (window.isOpen())
    {
/*
****************************************
Handle the players input
****************************************
*/
    if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
/*
****************************************make
Update the scene
****************************************
*/

/*
****************************************
Draw the scene
****************************************
*/
// Clear everything from the last frame
    window.clear();
// Draw our game scene here
    window.draw(spriteBackground);
    window.draw(spriteTree);
    window.draw(spriteBee);
    window.draw(spriteCloud1);
    window.draw(spriteCloud2); 
    window.draw(spriteCloud3);  
// Show everything we just drew
    window.display();
    }
return 0;
}