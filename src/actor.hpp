#ifndef __ACTOR_HPP__
#define __ACTOR_HPP__

#include <libtcod.hpp>
#include "defs.hpp"

class Attacker;
class Destructible;
class Ai;

class Actor
{
public:
	int x{0};
	int y{0};
	int ch{'@'};
	TCODColor col{TCODColor::white};
	const char *name;
	bool blocks{true}; // Can we walk on this actor
	Attacker *attacker{nullptr}; // Something that deals damage
	Destructible *destructible{nullptr}; // Something that can be damaged
	Ai *ai{nullptr}; // Something self-updating

	Actor() {}
	Actor(int x, int y, int ch, const char *name, const TCODColor &col);
	virtual ~Actor();

	void update();
	void render() const;
};

#endif
