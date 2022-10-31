#pragma once
#include <SDL/SDL.h>

#include "Render/Graphics.hpp""
#include "Timer.hpp"

class Application
{
private :
	Application();

public :
	static Application* instance();

	int run();

private :
	void pollEvents();

	static Application* p_application;
	Graphics m_graphics;
	SDL_Window* p_window;
	SDL_Event m_event;
	bool m_isRunning;

	Timer m_deltaClock;
};