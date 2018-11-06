#include <libtcod.hpp>
#include "engine.hpp"

Engine engine{80, 50};

int main()
{
	bool quit = false;
	
	while (!quit && !TCODConsole::isWindowClosed())
	{
		engine.update(quit);
		engine.render();
		TCODConsole::flush();
	}

	return 0;
}
