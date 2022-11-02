#include "Application.hpp"
#include "Settings.hpp"

Application* Application::p_application = nullptr;
Application::Application()
{
	m_isRunning = true;

	//Init sdl and graphics
	SDL_Init(SDL_INIT_EVERYTHING);
	p_window = SDL_CreateWindow(stg::TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, stg::WIDTH, stg::HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(p_window, -1, 0);
	m_graphics = Graphics(renderer);

	//Load scene
	m_scene.loadModel("../assets/teapot.obj");
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
	float angle = 0;
	while (m_isRunning)
	{
		this->pollEvents();

		float deltaTime = m_deltaClock.getElapsedTime() * 0.000001;
		m_deltaClock.restart();

		m_graphics.clear();

		angle += deltaTime;
		std::vector<Mesh>& sceneMeshes = m_scene.getMeshes();
		for (size_t i = 0; i < sceneMeshes.size(); i++)
		{
			for (size_t j = 0; j < sceneMeshes[i].faceIndex.size(); j++)
			{
				Vec2 a, b, c;
				Vec3 x, y, z;

				x = Math::rotateY(sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].a - 1], angle);
				y = Math::rotateY(sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].b - 1], angle);
				z = Math::rotateY(sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].c - 1], angle);

				x.z -= 4;
				y.z -= 4;
				z.z -= 4;

				a = Math::projectPerspective(x);
				b = Math::projectPerspective(y);
				c = Math::projectPerspective(z);

				m_graphics.drawTriangle
				(
					a,
					b,
					c,
					0xFF00FF00
				);
			}
		}
		

		m_graphics.render();
	}

	return EXIT_SUCCESS;
}
