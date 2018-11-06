#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <libtcod.hpp>
#include "bsplistener.hpp"
#include "defs.hpp"

struct Tile
{
	bool explored{false}; // Has the player seen this tile?
};

class Map
{
public:
	Map(int width, int height);
	virtual ~Map();

	bool isWall(int x, int y) const;
	bool isExplored(int x, int y) const;
	bool isInFov(int x, int y) const;
	bool canWalk(int x, int y) const;
	void computeFov();
	void addMonster(int x, int y);
	void update();
	bool moveOrAttack(int x, int y);
	void render() const;

protected:
	int width;
	int height;
	Tile *tiles;
	TCODMap *map;
	friend class BspListener;

	void dig(int x1, int y1, int x2, int y2);
	void createRoom(bool first, int x1, int y1, int x2, int y2);
};

#endif
