#include "bsplistener.hpp"
#include "map.hpp"

BspListener::BspListener(Map &map) : map(map) {}

bool BspListener::visitNode(TCODBsp *node, void *userData)
{
	if (node->isLeaf())
	{
		// Dig a room
		TCODRandom *rng = TCODRandom::getInstance();
		int w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
		int h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
		int x = rng->getInt(node->x+1, node->x + node->w - w - 1);
		int y = rng->getInt(node->y+1, node->y + node->h - h - 1);
		map.createRoom(roomNum == 0, x, y, x + w - 1, y + h - 1);

		if (roomNum != 0)
		{
			// Dig a corridor from last room
			map.dig(lastx, lasty, x + w / 2, lasty);
			map.dig(x + w / 2, lasty, x + w / 2, y + h / 2);
		}

		lastx = x + w / 2;
		lasty = y + h / 2;
		roomNum++;
	}
	return true;
}
