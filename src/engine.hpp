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

	void update(bool &quit);
	void render();

	TCODList<Actor*> actors;
	Actor *player;
	Map *world;
};

extern Engine engine;

#endif
