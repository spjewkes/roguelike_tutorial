#include <libtcod.hpp>

struct Tile
{
	bool canWalk{true}; // Can we walk through a tile?
};

class Map
{
public:
	Map(int width, int height) : width(width), height(height)
		{
			tiles = new Tile[width * height];
			setWall(30, 22);
			setWall(50, 22);
		}

	virtual ~Map()
		{
			delete [] tiles;
		}

	bool isWall(int x, int y) const
		{
			return !tiles[x + y * width].canWalk;
		}

	void render() const
		{
			static const TCODColor darkWall(0,0,100);
			static const TCODColor darkGround(50,50,150);

			for (int x=0; x<width; x++)
			{
				for (int y=0; y<height; y++)
				{
					if (isWall(x, y))
					{
						TCODConsole::root->setCharBackground(x, y, darkWall);
					}
					else
					{
						TCODConsole::root->setCharBackground(x, y, darkGround);
					}
				}
			}
		}

protected:
	int width;
	int height;
	Tile *tiles;

	void setWall(int x, int y)
		{
			tiles[x + y * width].canWalk = false;
		}
};
