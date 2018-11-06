#include "destructible.hpp"
#include "actor.hpp"
#include "engine.hpp"

Destructible::Destructible(float maxHp, float defence, const char *corpseName)
	: maxHp(maxHp), hp(maxHp), defence(defence), corpseName(corpseName)
{
}

float Destructible::takeDamage(Actor *owner, float damage)
{
	damage -= defence;
	if (damage > 0.0f)
	{
		hp -= damage;
		if (hp <= 0.0f)
		{
			die(owner);
		}
	}
	else
	{
		damage = 0.0f;
	}

	return damage;
}

void Destructible::die(Actor *owner)
{
	// Transforms the actor to a corpse
	owner->ch = '#';
	owner->col = TCODColor::darkRed;
	owner->name = corpseName;
	owner->blocks = false;

	// Make sure corpses are drawn before living actors
	engine.sendToBack(owner);
}

MonsterDestructible::MonsterDestructible(float maxHp, float defence, const char *corpseName)
	: Destructible(maxHp, defence, corpseName)
{
}

void MonsterDestructible::die(Actor *owner)
{
	// Transforms it into a nasty corpse! It doesn't block, can't be attacked and doesn't move
	printf("%s is dead\n", owner->name);
	Destructible::die(owner);
}

PlayerDestructible::PlayerDestructible(float maxHp, float defence, const char *corpseName)
	: Destructible(maxHp, defence, corpseName)
{
}

void PlayerDestructible::die(Actor *owner)
{
	printf("You died!\n");
	Destructible::die(owner);
	engine.gameStatus = Engine::DEFEAT;
}

