#pragma once

#include "led-matrix.h"

using rgb_matrix::Canvas;
using rgb_matrix::RGBMatrix;

class Renderer
{
public:
	Renderer(class Window* window, Canvas* canvas);
	~Renderer();
	void Render(class Game* game);
private:
	Canvas* canvas;
	class SDL_Renderer* m_renderer;
	uint32_t* m_colorBuffer;
	void RenderColorBuffer() const;
	void RenderProjection(class Player* player, struct Ray rays[], class Surfaces* surfaces) const;
};
