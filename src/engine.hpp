#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <libtcod.hpp>
#include "actor.hpp"
#include "map.hpp"

class Engine
{
public:
	Engine();
	virtual ~Engine();

	enum GameStatus
	{
		STARTUP,
		IDLE,
		NEW_TURN,
		VICTORY,
		DEFEAT,
	} gameStatus;

	void update(bool &quit);
	void render();

	TCODList<Actor*> actors;
	Actor *player;
	Map *world;
	int fovRadius{10};
};

extern Engine engine;

#endif
