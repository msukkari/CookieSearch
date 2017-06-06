#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

#include "Grid.h"


class Engine
{
public:
	bool Startup();
	void Run();
	void Shutdown();

	bool isRunning() { return m_Running; }

	static Engine* GetInstance()
	{
		if (!s_pInstance)
			s_pInstance = new Engine();

		return s_pInstance;
	}

	SDL_Window* getWindow() { return m_Window; }
	SDL_Surface* getScreenSurface() { return m_ScreenSurface; }

	static const int GRID_COUNT = 30;
	static const int GRID_WIDTH = 20;
	static const int GRID_SEPERATION = 2;
	static const int SCREEN_WIDTH = (GRID_WIDTH + GRID_SEPERATION) * GRID_COUNT - GRID_SEPERATION;


private:
	Engine() {};
	static Engine* s_pInstance;

	bool m_Running;
	bool m_LeftMouseButtonDown;
	bool m_RightMouseButtonDown;

	bool StartupSDL();
	void ShutdownSDL();

	SDL_Window* m_Window;
	SDL_Surface* m_ScreenSurface;

	Grid* m_Grid;
};

#endif // !ENGINE_H