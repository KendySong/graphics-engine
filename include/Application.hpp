#pragma once
#include <SDL/SDL.h>

#include "Graphics.hpp"

class Application
{
private :
	Application();

public :
	static Application* Instance();

	int Run();

private :
	void PollEvents();

	static Application* p_application;
	Graphics m_graphics;
	SDL_Window* p_window;
	SDL_Event m_event;
	bool m_isRunning;
};