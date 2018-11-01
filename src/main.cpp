#include <libtcod.hpp>
#include "actor.hpp"
#include "map.hpp"

int main()
{
	bool is_running = true;
	Actor player{40, 25, '@', TCODColor::white};
	Map world(80, 50);
	
	TCODConsole::initRoot(80,50,"libtcod C++ tutorial", false);
	while (is_running && !TCODConsole::isWindowClosed())
	{
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		switch(key.vk)
		{
		case TCODK_UP:
			player.y--;
			break;

		case TCODK_DOWN:
			player.y++;
			break;

		case TCODK_LEFT:
			player.x--;
			break;

		case TCODK_RIGHT:
			player.x++;
			break;

		case TCODK_ESCAPE:
			is_running = false;
			break;

		default:
			break;
		}

		TCODConsole::root->clear();
		world.render();
		player.render();
		TCODConsole::flush();
	}

	return 0;
}
