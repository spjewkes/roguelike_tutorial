#include "actor.hpp"
#include "engine.hpp"
#include "destructible.hpp"
#include "attacker.hpp"
#include "ai.hpp"

Actor::Actor(int x, int y, int ch, const char *name, const TCODColor &col)
	: x(x), y(y), ch(ch), col(col), name(name)
{
}

void Actor::update()
{
	if (ai)
	{
		ai->update(this);
	}
}

Actor::~Actor()
{
	delete attacker;
	delete destructible;
	delete ai;
}

void Actor::render() const
{
	TCODConsole::root->setChar(x,y,ch);
	TCODConsole::root->setCharForeground(x,y,col);
}
