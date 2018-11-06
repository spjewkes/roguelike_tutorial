#ifndef __AI_HPP__
#define __AI_HPP__

class Actor;

class Ai
{
public:
	Ai () {}
	virtual ~Ai() {}

	virtual void update(Actor *owner) = 0;
};

class PlayerAi : public Ai
{
public:
	PlayerAi() {}
	virtual ~PlayerAi() {}

	void update(Actor *owner);

protected:
	bool moveOrAttack(Actor *owner, int targetx, int targety);
};

class MonsterAi : public Ai
{
public:
	MonsterAi() {}
	virtual ~MonsterAi() {}

	void update(Actor *owner);

protected:
	bool moveOrAttack(Actor *owner, int targetx, int targety);

	int moveCount;
};

#endif
