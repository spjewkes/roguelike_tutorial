#include "engine.hpp"
#include "destructible.hpp"
#include "attacker.hpp"
#include "ai.hpp"

Engine::Engine(int screenWidth, int screenHeight)
	: gameStatus(STARTUP), screenWidth(screenWidth), screenHeight(screenHeight)
{
	TCODConsole::initRoot(screenWidth, screenHeight, "libtcod C++ tutorial", false);

	player = new Actor(40, 25, '@', "player", TCODColor::white);
	player->destructible = new PlayerDestructible(30, 2, "your cadaver");
	player->attacker = new Attacker(5);
	player->ai = new PlayerAi();
	actors.push(player);
	world = new Map(80, 45);
}

Engine::~Engine()
{
	actors.clearAndDelete();
	delete world;
}

void Engine::sendToBack(Actor *actor)
{
	actors.remove(actor);
	actors.insertBefore(actor, 0);
}

void Engine::update(bool &quit)
{
	if (gameStatus == STARTUP)
	{
		world->computeFov();
	}
	if (gameStatus == QUIT)
	{
		quit = true;
		return;
	}
	
	gameStatus = IDLE;
	quit = false;

	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL);
	player->update();

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

	player->render();
	TCODConsole::root->print(1, screenHeight = 2, "HP : %d/%d",
							 static_cast<int>(player->destructible->hp),
							 static_cast<int>(player->destructible->maxHp));
											  
}
