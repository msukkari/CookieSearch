#include <stdio.h>

#include "Engine.h"

Engine* Engine::s_pInstance = NULL;

bool Engine::Startup()
{
	if (!StartupSDL())
		return false;

	m_Running = true;
}

void Engine::Run()
{
	SDL_Event e;
	while (m_Running)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				m_Running = false;
		}

		// Fill surface with white background
		SDL_FillRect(m_ScreenSurface, NULL, SDL_MapRGB(m_ScreenSurface->format, 0xFF, 0xFF, 0xFF));

		for (int ROW = 0; ROW < GRID_COUNT; ROW++)
		{
			for (int COL = 0; COL < GRID_COUNT; COL++)
			{
				SDL_Rect boxRect;
				boxRect.x = ROW * (GRID_WIDTH + GRID_SEPERATION);
				boxRect.y = COL * (GRID_WIDTH + GRID_SEPERATION);
				boxRect.w = GRID_WIDTH;
				boxRect.h = GRID_WIDTH;

				SDL_FillRect(m_ScreenSurface, &boxRect, SDL_MapRGB(m_ScreenSurface->format, 0, 0, 0));
			}
		}

		SDL_UpdateWindowSurface(m_Window);
	}
}
void Engine::Shutdown()
{
	ShutdownSDL();
}

bool Engine::StartupSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		m_Window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_WIDTH,
			SDL_WINDOW_SHOWN);

		if (m_Window)
		{
			m_ScreenSurface = SDL_GetWindowSurface(m_Window);
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

void Engine::ShutdownSDL()
{
	SDL_FreeSurface(m_ScreenSurface);
	m_ScreenSurface = NULL;

	SDL_DestroyWindow(m_Window);
	m_Window = NULL;
}

