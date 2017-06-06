#include <ctime>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>

#include "Engine.h"
#include "Grid.h"
#include "Block.h"

void Grid::createAdjLists()
{
	int COUNT = Engine::GetInstance()->GRID_COUNT;
	for (Block* block : m_BlockList)
	{
		// Clear existing Adjlist
		block->m_AdjList.clear();

		int curRow = block->m_ID / COUNT;

		int top = block->m_ID - COUNT;	 // top
		if (top >= 0 && !m_BlockList[top]->m_Blocked)
			block->m_AdjList.push_back(top);


		int left = block->m_ID - 1;		// left
		if (left >= 0 && (left / COUNT) == curRow && !m_BlockList[left]->m_Blocked)
			block->m_AdjList.push_back(left);

		int right = block->m_ID + 1;	// right
		if (right >= 0 && (right / COUNT) == curRow && !m_BlockList[right]->m_Blocked)
			block->m_AdjList.push_back(right);

		int bot = block->m_ID + COUNT;  // bottom
		if (bot < (COUNT * COUNT) && !m_BlockList[bot]->m_Blocked)
			block->m_AdjList.push_back(bot);

		/*
		int topLeft = block->m_ID - COUNT - 1; // top left
		if (topLeft >= 0 && !m_BlockList[topLeft]->m_Blocked)
			block->m_AdjList.push_back(topLeft);

		int topRight = block->m_ID - COUNT + 1; // top right
		if (topRight >= 0 && !m_BlockList[topRight]->m_Blocked)
			block->m_AdjList.push_back(topRight);

		int botLeft = block->m_ID + COUNT - 1; // bottom left
		if (botLeft < (COUNT * COUNT) && !m_BlockList[botLeft]->m_Blocked)
			block->m_AdjList.push_back(botLeft);

		int botRight = block->m_ID + COUNT + 1; // bottom right
		if (botRight < (COUNT * COUNT) && !m_BlockList[botRight]->m_Blocked)
			block->m_AdjList.push_back(botRight);
		*/
	}

	
}
void Grid::Init(int COUNT, int WIDTH, int SEP)
{
	srand(time(NULL));

	m_Source = rand() % (WIDTH * WIDTH - 1);
	m_Destination = rand() % (WIDTH * WIDTH- 1);


	for (int ROW = 0; ROW < COUNT; ROW++)
	{
		for (int COL = 0; COL < COUNT; COL++)
		{
			Block* block = new Block();

			// Fill current block's RECT
			block->m_Rect.x = COL * (WIDTH + SEP);
			block->m_Rect.y = ROW * (WIDTH + SEP);
			block->m_Rect.w = WIDTH;
			block->m_Rect.h = WIDTH;

			// Set block ID
			block->m_ID = COL + (ROW * COUNT);

			// Set block visual color
			if (block->m_ID == m_Source)
			{
				// Initialize source to purple
				block->m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0x71, 0x20, 0x74);
			}
			else if (block->m_ID == m_Destination)
			{
				// initialize destination to red
				block->m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0xFF, 0, 0);
			}
			else
			{
				// Initialize color to black
				block->m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0, 0, 0);
			}

			// Initialize block color to white (not explored)
			// note: m_BlockColor is not the visual color of the block, see Block.h for explanation 
			block->m_BlockColor = Block::BLOCK_COLOR::WHITE;

			// All blocks are initially
			block->m_Blocked = false;

			// Add block to block list
			m_BlockList.push_back(block);
		}
	}

	createAdjLists();
}

void Grid::drawGrid()
{
	SDL_Surface* surface = Engine::GetInstance()->getScreenSurface();
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

	// Loop through block list and draw each block
	for (int i = 0; i < m_BlockList.size(); i++)
		SDL_FillRect(surface, &m_BlockList[i]->m_Rect, m_BlockList[i]->m_Color);

	SDL_UpdateWindowSurface(Engine::GetInstance()->getWindow());
}

int Grid::findBlock(int x, int y)
{
	for (int i = 0; i < m_BlockList.size(); i++)
	{
		Block* curBlock = m_BlockList[i];

		int x1 = curBlock->m_Rect.x;
		int x2 = curBlock->m_Rect.x + Engine::GetInstance()->GRID_WIDTH;
		int y1 = curBlock->m_Rect.y;
		int y2 = curBlock->m_Rect.y + Engine::GetInstance()->GRID_WIDTH;

		if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
			return curBlock->m_ID;
	}

	return -1;
}

void Grid::onBlockClick(int ID)
{
	if (ID != m_Source && ID != m_Destination) 
	{
		m_BlockList[ID]->m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0x69, 0x69, 0x69);
		m_BlockList[ID]->m_Blocked = true;
	}

}

std::vector<int> Grid::findShortestPath()
{
	std::vector<int> path;

	std::set<std::pair<int, int>> q;
	//q.insert(std::pair<int, int>(0, m_Source));

	createAdjLists();

	for (Block* b : m_BlockList)
	{
		if (!b->m_Blocked)
		{
			b->m_Distance = b->m_ID == m_Source ? 0 : INT_MAX;
			b->m_Pre = -1;
			b->m_BlockColor = Block::WHITE;

			//q.insert({ b->m_Distance, b->m_ID });
		}
	}

	q.insert({ 0, m_Source });

	bool run = true;
	while (!q.empty() && run)
	{
		int curID = q.begin()->second;
		q.erase(q.begin());

		Block* curBlock = m_BlockList[curID]; 

		if(curBlock->m_ID != m_Source && curBlock->m_ID != m_Destination)
			curBlock->m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0x4F, 0x4F, 0x4F);

		drawGrid();

		for (int e : m_BlockList[curID]->m_AdjList)
		{
			if (e >= 0 && e < m_BlockList.size())
			{
				Block* adjBlock = m_BlockList[e];
				if (adjBlock->m_Distance > m_BlockList[curID]->m_Distance + 1)
				{
					// Relax that edge (man)
					q.erase({ adjBlock->m_Distance, adjBlock->m_ID });
					adjBlock->m_Distance = curBlock->m_Distance + 1;
					q.insert({ curBlock->m_Distance + 1, adjBlock->m_ID });

					// if we relax the edge that means the current block is now the predecessor 
					adjBlock->m_Pre = curBlock->m_ID;
				}

				if (adjBlock->m_ID == m_Destination)
					run = false;
			}

		}

		if (curBlock->m_ID != m_Source && curBlock->m_ID != m_Destination)
			curBlock->m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0xE0, 0xE0, 0xE0);

		drawGrid();

	}

	// Step back from destination to find shortest path
	Block* block = m_BlockList[m_BlockList[m_Destination]->m_Pre];
	while (block->m_Pre != -1)
	{
		path.push_back(block->m_ID);
		block->m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0, 0xFF, 0);
		block = m_BlockList[block->m_Pre];
	}


	return path;
}