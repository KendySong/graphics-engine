#include "Application.hpp"
#include "Settings.hpp"

Application* Application::p_application = nullptr;
Application::Application()
{
	m_isRunning = true;

	SDL_Init(SDL_INIT_EVERYTHING);
	p_window = SDL_CreateWindow(stg::TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, stg::WIDTH, stg::HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(p_window, -1, 0);
	m_graphics = Graphics(renderer);
}

Application* Application::instance()
{
	if (p_application == nullptr)
	{
		p_application = new Application();
	}
	return p_application;
}

void Application::pollEvents()
{
	while (SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
			break;
		}
	}
}

int Application::run()
{
	while (m_isRunning)
	{
		this->pollEvents();

		//(milliseconds)
		float deltaTime = m_deltaClock.getElapsedTime();
		m_deltaClock.restart();

		m_graphics.clear();
		m_graphics.drawPixel(Vec2(200, 200), 0xFFFF00FF);
		m_graphics.render();
	}

	return EXIT_SUCCESS;
}
