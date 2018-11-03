#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <libtcod.hpp>
#include "bsplistener.hpp"

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;

struct Tile
{
	bool canWalk{false}; // Can we walk through a tile?
};

class Map
{
public:
	Map(int width, int height);
	virtual ~Map();

	bool isWall(int x, int y) const;
	void render() const;

protected:
	int width;
	int height;
	Tile *tiles;
	friend class BspListener;

	void dig(int x1, int y1, int x2, int y2);
	void createRoom(bool first, int x1, int y1, int x2, int y2);
	void setWall(int x, int y);
};

#endif
