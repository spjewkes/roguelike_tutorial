#include "engine.hpp"

Engine::Engine()
{
	TCODConsole::initRoot(80,50,"libtcod C++ tutorial", false);
	player = new Actor(40, 25, '@', TCODColor::white);
	actors.push(player);
	world = new Map(80, 45);
}

Engine::~Engine()
{
	actors.clearAndDelete();
	delete world;
}

void Engine::update(bool &quit)
{
	quit = false;
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch(key.vk)
	{
	case TCODK_UP:
		if (!world->isWall(player->x, player->y - 1))
		{
			player->y--;
		}
		break;

	case TCODK_DOWN:
		if (!world->isWall(player->x, player->y + 1))
		{
			player->y++;
		}
		break;

	case TCODK_LEFT:
		if (!world->isWall(player->x - 1, player->y))
		{
			player->x--;
		}
		break;

	case TCODK_RIGHT:
		if (!world->isWall(player->x + 1, player->y))
		{
			player->x++;
		}
		break;

	case TCODK_ESCAPE:
		quit = true;
		break;

	default:
		break;
	}
}

void Engine::render()
{
	TCODConsole::root->clear();
	world->render();
	for (auto actor : actors)
	{
		actor->render();
	}
}
