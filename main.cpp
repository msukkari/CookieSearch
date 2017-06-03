#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

const int GRID_COUNT = 20;
const int GRID_WIDTH = 20;
const int GRID_SEPERATION = 2;
const int SCREEN_WIDTH = (GRID_WIDTH + GRID_SEPERATION) * GRID_COUNT - GRID_SEPERATION;
const int SCREEN_HEIGHT = SCREEN_WIDTH;

SDL_Window* g_Window = NULL;
SDL_Surface* g_ScreenSurface = NULL;


bool StartupSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		g_Window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (g_Window)
		{
			g_ScreenSurface = SDL_GetWindowSurface(g_Window);
		}
		else
		{
			printf("Window could not be created: %s\n", SDL_GetError());
			return false;
		}
	}
	else
	{
		printf("SDL could not intiialize: %s\n", SDL_GetError());
		return false;
	}
}

void ShutdownSDL()
{
	SDL_FreeSurface(g_ScreenSurface);
	g_ScreenSurface = NULL;

	SDL_DestroyWindow(g_Window);
	g_Window = NULL;
}

int main(int argc, char* argv[])
{
	if (!StartupSDL())
		return -1;

	SDL_Event e;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				running = false;
		}

		// Fill surface with white background
		SDL_FillRect(g_ScreenSurface, NULL, SDL_MapRGB(g_ScreenSurface->format, 0xFF, 0xFF, 0xFF));
		
		for (int ROW = 0; ROW < GRID_COUNT; ROW++)
		{
			for (int COL = 0; COL < GRID_COUNT; COL++)
			{
				SDL_Rect boxRect;
				boxRect.x = ROW * (GRID_WIDTH + GRID_SEPERATION);
				boxRect.y = COL * (GRID_WIDTH + GRID_SEPERATION);
				boxRect.w = GRID_WIDTH;
				boxRect.h = GRID_WIDTH;

				SDL_FillRect(g_ScreenSurface, &boxRect, SDL_MapRGB(g_ScreenSurface->format, 0, 0, 0));
			}
		}

		SDL_UpdateWindowSurface(g_Window);
	}

	ShutdownSDL();

	return 0;
}