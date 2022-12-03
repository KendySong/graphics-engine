#include <cstring>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl.h>
#include <ImGui/imgui_impl_sdlrenderer.h>

#include "Graphics.hpp"
#include "../Settings.hpp"
#include "Color.hpp"

#include <iostream>
#include <random>

Graphics::Graphics(SDL_Renderer* renderer)
{
    srand(0);
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

void Graphics::drawFilledTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, std::uint32_t color)
{  
    Vec2 mid;
    Vec2 vertex[3];
    vertex[0] = pos1;
    vertex[1] = pos2;
    vertex[2] = pos3;
    
    bool isSort = false;
    while (!isSort)
    {
        isSort = true;
        for (size_t i = 0; i < 2; i++)
        {
            if (vertex[i].y > vertex[i + 1].y)
            {
                isSort = false;
                break;
            }
        }

        for (size_t i = 0; i < 2; i++)
        {
            if (vertex[i].y > vertex[i + 1].y)
            {
                Vec2 temp = vertex[i];
                vertex[i] = vertex[i + 1];
                vertex[i + 1] = temp;
            }
        }
    }

    mid.y = vertex[1].y;
    mid.x = ((vertex[1].y - vertex[0].y) * (vertex[2].x - vertex[0].x)) / (vertex[2].y - vertex[0].y) + vertex[0].x;

    this->drawFlatBotTriangle(vertex[0], vertex[1], mid, color);
    this->drawFLatTopTriangle(vertex[1], mid, vertex[2], color);
}

std::uint32_t Graphics::computeDirectionalLight(const DirectionalLight& light, const Vec3& surface, const Vec3& normal)
{
    /*
    std::uint32_t materialColor = WHITE;

    Vec3 ray = light.position - surface;
    float dot = Math::dot(Math::normalize(normal), ray);
    */

    std::uint32_t r = 0x00FF0000;
    std::uint32_t g = 0x0000FF00;
    std::uint32_t b = 0x000000FF;

    //multipy dot with color of light and material

    std::uint32_t finalColor = 0xFF000000 | (std::uint32_t)r | (std::uint32_t)g | (std::uint32_t)b;

    return finalColor;
}

bool Graphics::cullFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& camera)
{
    if (Math::dot(Math::cross(b - a, c - a), camera - a) > 0)
    {
        return false;
    }
    else 
    {
        return true;
    }
}

void Graphics::sortDepthFace(Mesh* mesh)
{
    
}

void Graphics::render() const
{
    SDL_UpdateTexture(p_frameTexture, NULL, p_frameBuffer, stg::WIDTH * sizeof std::uint32_t);
    SDL_RenderCopy(p_renderer, p_frameTexture, NULL, NULL);

    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(p_renderer);
}

void Graphics::drawFlatBotTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, std::uint32_t color)
{
    //Compute slope
    Vec2 p1 = pos1;
    Vec2 p2 = pos1;
    Vec2 delta1 = pos2 - pos1;
    Vec2 delta2 = pos3 - pos1;
    delta1 /= fabsf(delta1.y);
    delta2 /= fabsf(delta2.y);

    //Fill flat bottom triangle 
    for (size_t y = pos1.y + 1; y < pos2.y; y++)
    {
        this->drawLine(p1, p2, color);
        p1 += delta1;
        p2 += delta2;
    }
}

void Graphics::drawFLatTopTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, std::uint32_t color)
{
    Vec2 p1 = pos1;
    Vec2 p2 = pos2;
    Vec2 delta1 = pos1 - pos3;
    Vec2 delta2 = pos2 - pos3;
    delta1 /= fabsf(delta1.y);
    delta2 /= fabsf(delta2.y);

    float length = pos3.y - pos2.y;
    for (size_t y = 0; y < length; y++)
    {
        this->drawLine(p1, p2, color);
        p1 -= delta1;
        p2 -= delta2;
    }   
}