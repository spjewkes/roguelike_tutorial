#include <libtcod.hpp>
#include "engine.hpp"

int main()
{
	Engine engine;
	bool quit = false;
	
	while (!quit && !TCODConsole::isWindowClosed())
	{
		engine.update(quit);
		engine.render();
		TCODConsole::flush();
	}

	return 0;
}
