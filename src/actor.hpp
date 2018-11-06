#ifndef __ACTOR_HPP__
#define __ACTOR_HPP__

#include <libtcod.hpp>
#include "defs.hpp"

class Actor
{
public:
	int x{0};
	int y{0};
	int ch{'@'};
	char name[MAX_NAME_LENGTH];
	TCODColor col{TCODColor::white};

	Actor() {}
	Actor(int x, int y, int ch, const char *name, const TCODColor &col);

	bool moveOrAttack(int x, int y);
	void update();
	void render() const;
};

#endif
