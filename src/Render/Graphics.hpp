#pragma once
#include <cstdint>
#include <vector>

#include <SDL/SDL.h>

#include "Face.hpp"
#include "Mesh.hpp"
#include "../Math/Math.hpp"

class Graphics
{
public :
    Graphics() = default;

    Graphics(SDL_Renderer* renderer);

    void setFrameBuffer(std::uint32_t* frameBuffer)  noexcept;

    void clear(SDL_Window* window) const;

    void drawPixel(const Vec2& position, std::uint32_t color);
    void drawLine(const Vec2& pos1, const Vec2& pos2, std::uint32_t color);
    void drawRect(const Vec2& pos, const Vec2& size, std::uint32_t color);
    void drawTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, std::uint32_t color);
    void drawFilledTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, std::uint32_t color);

    bool cullFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& camera);

    void sortDepthFace(Mesh* mesh);

    void render() const;
    
private :
    void drawFlatBotTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, std::uint32_t color);
    void drawFLatTopTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, std::uint32_t color);

    std::uint32_t* p_frameBuffer;
    SDL_Renderer* p_renderer;
    SDL_Texture* p_frameTexture;
};