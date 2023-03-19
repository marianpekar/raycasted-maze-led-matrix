#include <iostream>
#include "renderer.h"
#include "SDL2/SDL.h"
#include "player.h"
#include "surfaces.h"
#include "constants.h"
#include "game.h"
#include "window.h"
#include "ray.h"

Renderer::Renderer(Window* window, Canvas* canvas)
{
    m_renderer = SDL_CreateRenderer(window->m_window, -1, 0);
    if (!m_renderer) {
        std::cout << "Error creating SDL renderer" << std::endl;
    }
	
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    m_colorBuffer = static_cast<uint32_t*>(malloc(sizeof(Uint32) * static_cast<Uint32>(WINDOW_WIDTH) * static_cast<Uint32>(WINDOW_HEIGHT)));

    this->canvas = canvas;
}

Renderer::~Renderer()
{
    free(m_colorBuffer);
    SDL_DestroyRenderer(m_renderer);
    delete canvas;
}

void Renderer::RenderProjection(Player* player, Ray rays[], Surfaces* surfaces) const
{
    for (auto i = 0; i < NUM_RAYS; i++) {
	    const auto perpendicularDistance = rays[i].m_distance * cos(rays[i].m_rayAngle - player->m_rotationAngle);
	    const float distanceToProjectionPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	    const float projectedWallHeight = (TILE_SIZE / perpendicularDistance) * distanceToProjectionPlane;

	    const auto wallStripHeight = static_cast<int>(projectedWallHeight);

        auto wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        auto wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

        for (auto ceilingPixel = 0; ceilingPixel <= wallTopPixel; ceilingPixel++) {
            m_colorBuffer[(WINDOW_WIDTH * ceilingPixel) + i] = 0xFF484848;
        }

        const auto surfaceId = rays[i].m_wallHitContent;

        const auto surfaceOffsetX = rays[i].m_wasHitVertical ? static_cast<int>(rays[i].m_wallHitY) % TILE_SIZE : static_cast<int>(rays[i].m_wallHitX) % TILE_SIZE;;

        for (auto y = wallTopPixel; y < wallBottomPixel; y++) {
	        const auto distanceFromTop = (y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2));
            const auto surfaceOffetY = distanceFromTop * (static_cast<float>(TEXTURE_HEIGHT) / wallStripHeight);

	        const auto texels = surfaces->m_textures[surfaceId];
	        const auto texel = Surfaces::GetPixel(texels, surfaceOffsetX, surfaceOffetY);
        	
            auto darkenAmount = rays[i].m_wasHitVertical ? perpendicularDistance * 0.001f : 0.3f + perpendicularDistance * 0.001f;
            if (darkenAmount > 0.6f)
                darkenAmount = 0.6f;

            m_colorBuffer[(WINDOW_WIDTH * y) + i] = Surfaces::Darken(texel, darkenAmount);
        }

        for (auto floorPixel = wallBottomPixel; floorPixel < WINDOW_HEIGHT; floorPixel++) {
            m_colorBuffer[(WINDOW_WIDTH * floorPixel) + i] = 0xFF808080;
        }
    }
}

void Renderer::RenderColorBuffer() const
{
    for (auto x = 0; x < WINDOW_WIDTH; x++) {
        for (auto y = 0; y < WINDOW_HEIGHT; y++) {
            uint32_t color = m_colorBuffer[(WINDOW_WIDTH * y) + x];

            uint8_t b = (color >> 16) & 0xFF;
            uint8_t g = (color >> 8) & 0xFF;
            uint8_t r = color & 0xFF;
            
            canvas->SetPixel(x, y, r, g, b);
        }
    }
}

void Renderer::Render(Game* game)
{
    RenderProjection(game->m_player, game->m_rays, game->m_surfaces);
    RenderColorBuffer();
}
