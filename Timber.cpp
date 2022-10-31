// Include important libraries here
#include <SFML/Graphics.hpp>
// Make code easier to type with "using namespace"
using namespace sf;
// This is where our game starts from
int main()
{
// Create a video mode object
VideoMode vm(800,600);//resolution // 1366x 768//1280x720//1024x768//800x600
// Create and open a window for the game
RenderWindow window(vm,"Timber!!!");//, Style::Fullscreen) for  full screen
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
// Show everything we just drew
    window.display();
    }
return 0;
}