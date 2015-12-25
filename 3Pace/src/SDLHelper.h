#pragma once
#include <string>
#include <SDL.h>
#undef main
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <exception>

class SDLHelper
{
public:
	SDLHelper(std::string title, int x, int y, int w, int h);
	~SDLHelper();

	void loop();

private:
	bool mRunning;
	SDL_Window* mDisplayWindow;
	SDL_GLContext mGlContext;
};

