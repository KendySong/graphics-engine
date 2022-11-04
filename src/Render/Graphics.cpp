#include <cstring>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl.h>
#include <ImGui/imgui_impl_sdlrenderer.h>

#include "Graphics.hpp"
#include "../Settings.hpp"

Graphics::Graphics(SDL_Renderer* renderer)
{
    p_renderer = renderer;
    p_frameBuffer = new std::uint32_t[stg::WIDTH * stg::HEIGHT];
    p_frameTexture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, stg::WIDTH, stg::HEIGHT);
}

void Graphics::setFrameBuffer(std::uint32_t* frameBuffer) noexcept
{
    p_frameBuffer = frameBuffer;
}

void Graphics::clear(SDL_Window* window) const
{
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
    SDL_RenderClear(p_renderer);
    memset(p_frameBuffer, 0, stg::WIDTH * stg::HEIGHT * sizeof std::uint32_t);

    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();
}

void Graphics::drawPixel(const Vec2& position, std::uint32_t color)
{
    if (position.x >= 0 && position.x < stg::WIDTH && position.y >= 0  && position.y < stg::HEIGHT)
    {
        p_frameBuffer[(int)(stg::WIDTH * (int)position.y + (int)position.x)] = color;
    }
}

void Graphics::drawLine(const Vec2& pos1, const Vec2& pos2, std::uint32_t color)
{
    Vec2 delta = pos2 - pos1;
    Vec2 start = pos1;
    float length = fabsf(delta.x) >= fabsf(delta.y) ? fabsf(delta.x) : fabsf(delta.y);

    //Find increment values in x and y
    Vec2 inc(delta.x / length, delta.y / length);

    for (size_t i = 0; i <= length; i++)
    {
        this->drawPixel(start, color);
        start += inc;
    }
}

void Graphics::drawRect(const Vec2& pos, const Vec2& size, std::uint32_t color)
{
    Vec2 max = pos + size;
    for (size_t y = pos.y; y < max.y; y++)
    {
        for (size_t x = pos.x; x < max.x; x++)
        {
            this->drawPixel(Vec2(x, y), color);
        }
    }
}

void Graphics::drawTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, std::uint32_t color)
{
    this->drawLine(pos1, pos2, color);
    this->drawLine(pos2, pos3, color);
    this->drawLine(pos3, pos1, color);
}

bool Graphics::cullFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& camera)
{
    if (Math::dot(Math::normalize(Math::cross(b - a, c - a)), camera - a) > 2)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void Graphics::render() const
{
    SDL_UpdateTexture(p_frameTexture, NULL, p_frameBuffer, stg::WIDTH * sizeof std::uint32_t);
    SDL_RenderCopy(p_renderer, p_frameTexture, NULL, NULL);

    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(p_renderer);
}