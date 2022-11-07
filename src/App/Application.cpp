#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl.h>
#include <ImGui/imgui_impl_sdlrenderer.h>

#include "Application.hpp"
#include "../Settings.hpp"

Application* Application::p_application = nullptr;
Application::Application()
{
	m_fps = 0;
	m_isRunning = true;

	//Init sdl and graphics
	SDL_Init(SDL_INIT_EVERYTHING);
	p_window = SDL_CreateWindow(stg::TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, stg::WIDTH, stg::HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(p_window, -1, 0);
	m_graphics = Graphics(renderer);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(p_window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	m_sandBox.load();
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
		ImGui_ImplSDL2_ProcessEvent(&m_event);
		switch (m_event.type)
		{
		case SDL_QUIT :
			m_isRunning = false;
			break;
		}
	}
}

int Application::run()
{	
	char m_fpsBuffer[10];
	while (m_isRunning)
	{
		this->pollEvents();

		m_fps++;
		if (m_framerateClock.getElapsedTime() >= 1)
		{	
			snprintf(m_fpsBuffer, sizeof(m_fpsBuffer), "FPS : %i", m_fps);
			m_fps = 0;
			m_framerateClock.restart();
		}

		float deltaTime = m_deltaClock.getElapsedTime();
		m_deltaClock.restart();
		m_sandBox.update(deltaTime);

		m_graphics.clear(p_window);
		m_sandBox.draw(m_graphics);
		ImGui::Begin("Rendering Info");
		ImGui::TextUnformatted(m_fpsBuffer);
		ImGui::Text("Frame time : %f ms", deltaTime * 1000);
		ImGui::End();
		m_graphics.render();
	}

	return EXIT_SUCCESS;
}
