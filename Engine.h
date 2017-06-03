#pragma once

class Engine
{
public:
	bool Startup();
	void Shutdown();

	static const int GRID_COUNT = 10;
	static const int GRID_WIDTH = 50;
	static const int GRID_SEPERATION = 5;
	static const int SCREEN_WIDTH = (GRID_WIDTH + GRID_SEPERATION) * 10 - GRID_SEPERATION;

private:
	Engine() {};

	SDL_Window* m_Window;
	SDL_Surface* g_ScreenSurface;
};