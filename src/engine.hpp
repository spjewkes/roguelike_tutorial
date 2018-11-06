#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <libtcod.hpp>
#include "actor.hpp"
#include "map.hpp"

class Engine
{
public:
	Engine(int screenWidth, int screenHeight);
	virtual ~Engine();

	enum GameStatus
	{
		STARTUP,
		IDLE,
		NEW_TURN,
		VICTORY,
		DEFEAT,
		QUIT,
	} gameStatus;

	void sendToBack(Actor *actor);

	void update(bool &quit);
	void render();

	TCODList<Actor*> actors;
	Actor *player;
	Map *world;
	int fovRadius{10};

	int screenWidth;
	int screenHeight;
	TCOD_key_t lastKey;
};

extern Engine engine;

#endif
