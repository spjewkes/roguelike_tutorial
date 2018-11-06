#include <cmath>
#include "ai.hpp"
#include "actor.hpp"
#include "defs.hpp"
#include "destructible.hpp"
#include "engine.hpp"
#include "attacker.hpp"

void PlayerAi::update(Actor *owner)
{
	if (owner->destructible && owner->destructible->isDead())
	{
		return;
	}

	int dx = 0;
	int dy = 0;

	switch (engine.lastKey.vk)
	{
	case TCODK_UP:
		dy = -1;
		break;

	case TCODK_DOWN:
		dy = 1;
		break;

	case TCODK_LEFT:
		dx = -1;
		break;

	case TCODK_RIGHT:
		dx = 1;
		break;

	case TCODK_ESCAPE:
		engine.gameStatus = Engine::QUIT;
		break;

	default:
		break;
	}

	if ((engine.gameStatus != Engine::QUIT) &&
		(dx != 0 || dy != 0))
	{
		engine.gameStatus = Engine::NEW_TURN;
		if (moveOrAttack(owner, owner->x + dx, owner->y + dy))
		{
			engine.world->computeFov();
		}
	}
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetx, int targety)
{
	if (engine.world->isWall(targetx, targety))
	{
		return false;
	}

	for (Actor *actor : engine.actors)
	{
		if (actor->destructible && !actor->destructible->isDead() &&
			actor->x == targetx && actor->y == targety)
		{
			owner->attacker->attack(owner, actor);
			return false;
		}
	}

	// Look for corpses
	for (Actor *actor : engine.actors)
	{
		if (actor->destructible && actor->destructible->isDead() &&
			actor->x == targetx && actor->y == targety)
		{
			printf("There's a %s here.\n", actor->name);
		}
	}

	owner->x = targetx;
	owner->y = targety;

	return true;
}

void MonsterAi::update(Actor *owner)
{
	if (owner->destructible && owner->destructible->isDead())
	{
		return;
	}

	if (engine.world->isInFov(owner->x, owner->y))
	{
		// We can see the player. Move toward them.
		moveCount = TRACKING_TURNS;
	}
	else
	{
		moveCount--;
	}

	if (moveCount > 0)
	{
		moveOrAttack(owner, engine.player->x, engine.player->y);
	}
}

bool MonsterAi::moveOrAttack(Actor *owner, int targetx, int targety)
{
	int dx = targetx - owner->x;
	int dy = targety - owner->y;
	int stepx = (dx > 0 ? 1 : -1);
	int stepy = (dy > 0 ? 1 : -1);

	float distance = std::sqrtf(static_cast<float>(dx * dx + dy * dy));

	if (distance >= 2.0f)
	{
		dx = static_cast<int>(std::round(dx / distance));
		dy = static_cast<int>(std::round(dy / distance));

		if (engine.world->canWalk(owner->x + dx, owner->y + dy))
		{
			owner->x += dx;
			owner->y += dy;
		}
		else if (engine.world->canWalk(owner->x + stepx, owner->y))
		{
			owner->x += stepx;
		}
		else if (engine.world->canWalk(owner->x, owner->y + stepy))
		{
			owner->y += stepy;
		}
		else if (owner->attacker)
		{
			owner->attacker->attack(owner, engine.player);
		}
	}
}
