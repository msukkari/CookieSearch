#include <stdio.h>

#include "Engine.h"

Engine* Engine::s_pInstance = NULL;

bool Engine::Startup()
{
	if (!StartupSDL())
		return false;

	m_Grid = new Grid();
	m_Grid->Init();

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
			else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				int clicked_ID = m_Grid->findBlock(e.button.x, e.button.y);
				if (clicked_ID != -1)
					m_Grid->onBlockClick(clicked_ID);
			}
		}

		// Fill surface with white background
		SDL_FillRect(m_ScreenSurface, NULL, SDL_MapRGB(m_ScreenSurface->format, 0xFF, 0xFF, 0xFF));

		m_Grid->drawGridOntoSurface(m_ScreenSurface);

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

