#include <libtcod.hpp>

class Actor
{
public:
	int x{0};
	int y{0};
	int ch{'@'};
	TCODColor col{TCODColor::white};

	Actor() {}
	Actor(int x, int y, int ch, const TCODColor &col) : x(x), y(y), ch(ch), col(col) {}

	void render() const
		{
			TCODConsole::root->setChar(x,y,ch);
			TCODConsole::root->setCharForeground(x,y,col);
		}
};
