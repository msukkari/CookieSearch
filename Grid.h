#ifndef GRID_H
#define GRID_H

#include <vector>

#include "Block.h"

class Grid
{
public:
	Grid() {}

	void Init(int, int, int);

	void drawGrid();
	int findBlock(int x, int y);

	void onBlockClick(int ID);
	void createAdjLists();

	std::vector<int> findShortestPath();

private:
	std::vector<Block*> m_BlockList;

	int m_Source;
	int m_Destination;
};
#endif // !GRID_H
