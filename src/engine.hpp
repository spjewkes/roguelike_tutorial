#include <libtcod.hpp>
#include "actor.hpp"
#include "map.hpp"

class Engine
{
public:
	Engine()
		{
			TCODConsole::initRoot(80,50,"libtcod C++ tutorial", false);
			player = new Actor(40, 25, '@', TCODColor::white);
			actors.push(player);
			actors.push(new Actor(60, 13, '@', TCODColor::yellow));
			world = new Map(80, 50);
		}

	virtual ~Engine()
		{
			actors.clearAndDelete();
			delete world;
		}

	void update(bool &quit)
		{
			quit = false;
			TCOD_key_t key;
			TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
			switch(key.vk)
			{
			case TCODK_UP:
				player->y--;
				break;

			case TCODK_DOWN:
				player->y++;
				break;

			case TCODK_LEFT:
				player->x--;
				break;

			case TCODK_RIGHT:
				player->x++;
				break;

			case TCODK_ESCAPE:
				quit = true;
				break;

			default:
				break;
			}
		}

	void render()
		{
			TCODConsole::root->clear();
			world->render();
			for (auto actor : actors)
			{
				actor->render();
			}
		}

private:
	TCODList<Actor*> actors;
	Actor *player;
	Map *world;
};
