#ifndef __ACTOR_HPP__
#define __ACTOR_HPP__

#include <libtcod.hpp>

class Actor
{
public:
	int x{0};
	int y{0};
	int ch{'@'};
	TCODColor col{TCODColor::white};

	Actor() {}
	Actor(int x, int y, int ch, const TCODColor &col);

	void render() const;
};

#endif
