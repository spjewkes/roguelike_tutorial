#include "actor.hpp"
#include "engine.hpp"

Actor::Actor(int x, int y, int ch, const char *name, const TCODColor &col)
	: x(x), y(y), ch(ch), col(col)
{
	strcpy(this->name, name);
}

void Actor::update()
{
	printf("The %s growls!\n", name);
}

bool Actor::moveOrAttack(int x, int y)
{
	if (engine.world->isWall(x, y))
	{
		return false;
	}

	for (Actor *actor : engine.actors)
	{
		if (actor->x == x && actor->y == y)
		{
			printf("The %s laughs at your puny efforts to attack him!\n", actor->name);
			return false;
		}
	}

	this->y = y;
	this->x = x;

	return true;
}

void Actor::render() const
{
	TCODConsole::root->setChar(x,y,ch);
	TCODConsole::root->setCharForeground(x,y,col);
}
