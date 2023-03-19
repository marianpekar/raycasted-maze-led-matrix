#pragma once

#include "constants.h"

class Window
{
public:
	Window();
	~Window();
	class SDL_Window* m_window;
};

