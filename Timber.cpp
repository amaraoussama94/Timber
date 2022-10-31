// Include important libraries here
#include <SFML/Graphics.hpp>
// Make code easier to type with "using namespace"
using namespace sf;
// This is where our game starts from
int main()
{
// Create a video mode object
VideoMode vm(1920, 1080);
// Create and open a window for the game
RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
return 0;
}