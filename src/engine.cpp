#include "engine.hpp"

Engine::Engine() : gameStatus(STARTUP)
{
	TCODConsole::initRoot(80,50,"libtcod C++ tutorial", false);
	player = new Actor(40, 25, '@', "player", TCODColor::white);
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
	if (gameStatus == STARTUP)
	{
		world->computeFov();
	}
	gameStatus = IDLE;

	int dx = 0;
	int dy = 0;
	quit = false;

	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch(key.vk)
	{
	case TCODK_UP:
		if (!world->isWall(player->x, player->y - 1))
		{
			dy = -1;
		}
		break;

	case TCODK_DOWN:
		if (!world->isWall(player->x, player->y + 1))
		{
			dy = 1;
		}
		break;

	case TCODK_LEFT:
		if (!world->isWall(player->x - 1, player->y))
		{
			dx = -1;
		}
		break;

	case TCODK_RIGHT:
		if (!world->isWall(player->x + 1, player->y))
		{
			dx = 1;
		}
		break;

	case TCODK_ESCAPE:
		quit = true;
		break;

	default:
		break;
	}

	if (dx != 0 || dy != 0)
	{
		gameStatus = NEW_TURN;
		if (player->moveOrAttack(player->x + dx, player->y + dy))
		{
			world->computeFov();
		}
	}

	if (gameStatus == NEW_TURN)
	{
		for (Actor *actor : actors)
		{
			if (actor != player)
			{
				actor->update();
			}
		}
	}
}

void Engine::render()
{
	TCODConsole::root->clear();
	world->render();
	for (auto actor : actors)
	{
		if (world->isInFov(actor->x, actor->y))
		{
			actor->render();
		}
	}
}
