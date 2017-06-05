#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>
#include <vector>

class Block
{
public:
	Block() {}

	// note: this is not the visual color of the block
	enum BLOCK_COLOR
	{
		WHITE, // not explored
		GREY, // currently exploring (ie. relaxing adj edges)
		BLACK // explored
	};

	SDL_Rect m_Rect;

	BLOCK_COLOR m_BlockColor;

	Uint32 m_Color;
	int m_ID;
	int m_Distance;
	int m_Pre;

	bool m_Blocked;


	std::vector<int> m_AdjList;

};

#endif // !BLOCK_H
