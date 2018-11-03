#ifndef __BSPLISTENER_HPP__
#define __BSPLISTENER_HPP__

#include <libtcod.hpp>

class Map;

class BspListener : public ITCODBspCallback
{
public:
	BspListener(Map &map);

	bool visitNode(TCODBsp *node, void *userData);
	
private:
	Map &map; // Map to dig
	int roomNum{0}; // Room number
	int lastx{0}, lasty{0}; // Centre of last room
};

#endif
