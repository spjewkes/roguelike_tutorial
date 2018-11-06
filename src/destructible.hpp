#ifndef __DESTRUCTIBLE_HPP__
#define __DESTRUCTIBLE_HPP__

class Actor;

class Destructible
{
public:
	Destructible(float maxHp, float defence, const char *corpseName);
	virtual ~Destructible() {}

	inline bool isDead() { return hp <= 0; }
	float takeDamage(Actor *owner, float damage);
	virtual void die(Actor *owner);

	float maxHp; // Maximum health points
	float hp; // Current health points
	float defence; // Hit points deflected
	const char *corpseName; // The actor's name once dead/destroyed
};

class MonsterDestructible : public Destructible
{
public:
	MonsterDestructible(float maxHp, float defence, const char *corpseName);
	virtual ~MonsterDestructible() {}
	
	void die(Actor *owner);
};

class PlayerDestructible : public Destructible
{
public:
	PlayerDestructible(float maxHp, float defence, const char *corpseName);
	virtual ~PlayerDestructible() {}

	void die(Actor *owner);
};

#endif
