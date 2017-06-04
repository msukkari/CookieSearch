#include <ctime>

#include "Engine.h"
#include "Grid.h"
#include "Block.h"

void Grid::Init()
{
	int count = Engine::GetInstance()->GRID_COUNT;
	int width = Engine::GetInstance()->GRID_WIDTH;
	int sep	= Engine::GetInstance()->GRID_SEPERATION;

	srand(time(NULL));

	m_Source = rand() % (width * width - 1);
	m_Destination = rand() % (width * width - 1);

	for (int ROW = 0; ROW < width; ROW++)
	{
		for (int COL = 0; COL < width; COL++)
		{
			Block block;

			// Fill current block's RECT
			block.m_Rect.x = ROW * (width + sep);
			block.m_Rect.y = COL * (width + sep);
			block.m_Rect.w = width;
			block.m_Rect.h = width;

			// Set block ID
			block.m_ID = COL + (ROW * width);

			if (block.m_ID == m_Source)
			{
				// Initialize source to green
				block.m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0x71, 0x20, 0x74);
			}
			else if (block.m_ID == m_Destination)
			{
				// initialize destination to red
				block.m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0xFF, 0, 0);
			}
			else
			{
				// Initialize color to black
				block.m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0, 0, 0);
			}


			// Add block to block list
			m_BlockList.push_back(block);
		}
	}
}

void Grid::drawGridOntoSurface(SDL_Surface* surface)
{
	// Loop through block list and draw each block
	for (int i = 0; i < m_BlockList.size(); i++)
		SDL_FillRect(surface, &m_BlockList[i].m_Rect, m_BlockList[i].m_Color);
}

int Grid::findBlock(int x, int y)
{
	for (int i = 0; i < m_BlockList.size(); i++)
	{
		Block curBlock = m_BlockList[i];

		int x1 = curBlock.m_Rect.x;
		int x2 = curBlock.m_Rect.x + Engine::GetInstance()->GRID_WIDTH;
		int y1 = curBlock.m_Rect.y;
		int y2 = curBlock.m_Rect.y + Engine::GetInstance()->GRID_WIDTH;

		if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
			return curBlock.m_ID;
	}

	return -1;
}

void Grid::onBlockClick(int ID)
{
	if(ID != m_Source && ID != m_Destination)
		m_BlockList[ID].m_Color = SDL_MapRGB(Engine::GetInstance()->getScreenSurface()->format, 0x69, 0x69, 0x69);
}