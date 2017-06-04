#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>

class Block
{
public:
	Block() {}

	SDL_Rect m_Rect;
	Uint32 m_Color;
	int m_ID;
};

#endif // !BLOCK_H
