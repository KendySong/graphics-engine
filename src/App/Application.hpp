#pragma once
#include <SDL/SDL.h>

#include "Timer.hpp"
#include "Sandbox.hpp"
#include "../Render/Graphics.hpp"
#include "../Render/Scene.hpp"

class Application
{
private :
	Application();

public :
	static Application* instance() noexcept;

	int run();

private :
	void pollEvents();

	static Application* p_application;
	Graphics m_graphics;
	SDL_Window* p_window;
	SDL_Event m_event;
	bool m_isRunning;

	Timer m_deltaClock;
	Sandbox m_sandBox;

	Timer m_framerateClock;
	unsigned int m_fps;
};