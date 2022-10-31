#pragma once
#include <cstdint>

#include <SDL/SDL.h>

class Graphics
{
private :
    Graphics(SDL_Renderer* renderer);

public :
    void setFrameBuffer(std::uint32_t frameBuffer);

    void clear();

    void render();
    
private :
    std::uint32_t p_frameBuffer;
    SDL_Renderer* p_renderer;
    SDL_Texture* p_frameTexture;
};