#include <stdio.h>

#include "Engine.h"

Engine* Engine::s_pInstance = NULL;

bool Engine::Startup()
{
	if (!StartupSDL())
		return false;

	m_Grid = new Grid();
	m_Grid->Init(GRID_COUNT, GRID_WIDTH, GRID_SEPERATION);

	m_Running = true;
	m_MouseButtonDown = false;
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
			else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				/*
				int clicked_ID = m_Grid->findBlock(e.button.x, e.button.y);
				if (clicked_ID != -1)
					m_Grid->onBlockClick(clicked_ID);
				*/
				m_MouseButtonDown = true;
			}
			else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
			{
				m_MouseButtonDown = false;
			}
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
			{
				std::vector<int> path = m_Grid->findShortestPath();
			}
		}

		if (m_MouseButtonDown)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			int clicked_ID = m_Grid->findBlock(x, y);
			if (clicked_ID != -1)
				m_Grid->onBlockClick(clicked_ID);
		}

		m_Grid->drawGrid();
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
		m_Window = SDL_CreateWindow("Cookie Search", SDL_WINDOWPOS_UNDEFINED,
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

