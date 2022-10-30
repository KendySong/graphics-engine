#include "Application.hpp"
#include "Settings.hpp"

Application* Application::p_application = nullptr;
Application::Application()
{
	m_isRunning = true;

	SDL_Init(SDL_INIT_EVERYTHING);
	p_window = SDL_CreateWindow(stg::TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, stg::WIDTH, stg::HEIGHT, SDL_WINDOW_SHOWN);
}

Application* Application::Instance()
{
	if (p_application == nullptr)
	{
		p_application = new Application();
	}
	return p_application;
}

int Application::Run()
{
	while (m_isRunning)
	{
		while (SDL_PollEvent(&m_event))
		{
			if (m_event.type == SDL_QUIT)
			{
				return 0;
			}
		}
	}
	
}
