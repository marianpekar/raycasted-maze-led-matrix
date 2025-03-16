#pragma once

#include "constants.h"

class Surfaces
{
public:
	Surfaces();
	uint32_t* m_textures[NUM_TEXTURES + 1];
	static uint32_t GetPixel(uint32_t* texels, int x, int y);
	static int Darken(const int& color, const float& amount);
private:
	static uint32_t* LoadPixels(const char* filePath);
};

