#include <vector>

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
	std::vector<Vec3> points;
	for (float x = -1; x < 1; x += 0.25)
	{
		for (float y = -1; y < 1; y += 0.25)
		{
			for (float z = -1; z < 1; z += 0.25)
			{
				points.emplace_back(x, y, z);
			}
		}
	}

	float angle = 0;
	while (m_isRunning)
	{
		this->pollEvents();

		float deltaTime = m_deltaClock.getElapsedTime() * 0.000001;
		m_deltaClock.restart();

		m_graphics.clear();

		angle += deltaTime;
		for (size_t i = 0; i < points.size(); i++)
		{
			Vec3 rotated = Math::rotateZ(points[i], angle);
			rotated.z -= 5;
			Vec2 pos = Math::projectPerspective(rotated);
			m_graphics.drawPixel(pos, 0xFF00FF00);
		}

		m_graphics.render();
	}

	return EXIT_SUCCESS;
}
