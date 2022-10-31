#pragma once
#include <SDL/SDL.h>

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
	SDL_Window* p_window;
	SDL_Renderer* p_renderer;
	SDL_Event m_event;
	bool m_isRunning;
};