#ifndef GRID_H
#define GRID_H

#include <vector>

#include "Block.h"

class Grid
{
public:
	Grid() {}

	void Init();

	void drawGridOntoSurface(SDL_Surface* surface);
	int findBlock(int x, int y);

	void onBlockClick(int ID);

private:
	std::vector<Block> m_BlockList;

	int m_Source;
	int m_Destination;
};
#endif // !GRID_H
