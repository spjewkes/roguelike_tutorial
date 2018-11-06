#ifndef __ATTACKER_HPP__
#define __ATTACKER_HPP__

class Actor;

class Attacker
{
public:
	Attacker(float power);

	void attack(Actor *owner, Actor *target);

	float power; // Hit points given
};

#endif
