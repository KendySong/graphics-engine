#pragma once
#include <cstdint>

#include <SDL/SDL.h>

#include "../Math/Vec2.hpp"

class Graphics
{
public :
    Graphics() = default;

    Graphics(SDL_Renderer* renderer);

    void setFrameBuffer(std::uint32_t* frameBuffer);

    void clear();

    void drawPixel(const Vec2& position, std::uint32_t color);

    void drawLine(const Vec2& pos1, const Vec2& pos2);

    void render();
    
private :
    std::uint32_t* p_frameBuffer;
    SDL_Renderer* p_renderer;
    SDL_Texture* p_frameTexture;
};