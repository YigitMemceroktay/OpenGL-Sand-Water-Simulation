#include "OpenGL/Window.h"

int main()
{
	Engine::Window*  window = new Engine::Window("OpenGL",1000,1000);

	window->Init();
	window->GameLoop();


	return 0;
}