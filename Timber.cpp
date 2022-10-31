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
// Show everything we just drew
    window.display();
    }
return 0;
}