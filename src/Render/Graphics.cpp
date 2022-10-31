#include <cstring>

#include "Graphics.hpp"
#include "../Settings.hpp"

Graphics::Graphics(SDL_Renderer* renderer)
{
    p_renderer = renderer;
    p_frameBuffer = new std::uint32_t[stg::WIDTH * stg::HEIGHT];
    p_frameTexture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, stg::WIDTH, stg::HEIGHT);
}

void Graphics::setFrameBuffer(std::uint32_t* frameBuffer)
{
    p_frameBuffer = frameBuffer;
}

void Graphics::clear()
{
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
    SDL_RenderClear(p_renderer);
    memset(p_frameBuffer, 0, stg::WIDTH * stg::HEIGHT * sizeof std::uint32_t);
}

void Graphics::drawPixel(const Vec2& position, std::uint32_t color)
{
    p_frameBuffer[(int)(stg::WIDTH * (int)position.y + (int)position.x)] = color;
}

void Graphics::render()
{
    SDL_UpdateTexture(p_frameTexture, NULL, p_frameBuffer, stg::WIDTH * sizeof std::uint32_t);
    SDL_RenderCopy(p_renderer, p_frameTexture, NULL, NULL);
    SDL_RenderPresent(p_renderer);
}