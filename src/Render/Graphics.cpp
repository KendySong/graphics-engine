#include <cstring>

#include "Graphics.hpp"
#include "Settings.hpp"

Graphics::Graphics(SDL_Renderer* renderer)
{
    p_renderer = renderer;
    p_frameBuffer = new std::uint32_t[stg::WIDTH * stg::HEIGHT];
    p_frameTexture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, stg::WIDTH, stg::HEIGHT);
}

void Graphics::setFrameBuffer(std::uint32_t frameBuffer)
{
    p_frameBuffer = frameBuffer;
}

void Graphics::clear()
{
    memset(p_frameTexture, 0, stg::WIDTH * stg::HEIGHT * sizeof std::uint32_t);
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
    SDL_RenderClear();
}

void Graphics::render()
{
    SDL_UpdateTexture(p_frameTexture, NULL, p_frameBuffer, stg::WIDTH * sizeof std::uint32_t);
    SDL_RenderCopy();
    SDL_RenderPresent();
}