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
	world = new Map(80, 43);
	gui = new Gui();

	gui->message(TCODColor::red, "Welcome stranger!\nPrepare to perish in the Tombs of the Ancient Kings.");
}

Engine::~Engine()
{
	actors.clearAndDelete();
	delete world;
	delete gui;
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

	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &lastKey, &mouse);
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
	gui->render();
}
