#pragma once
#include <SDL.h>
#include <SDL_image.h>
#undef main
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <iostream>
#include <string>
#include <exception>
class SDLHelper {
public:
	SDLHelper(std::string title, int x, int y, int w, int h);
	~SDLHelper();

	void loop();

private:
	bool mRunning;
	GLuint mProgramID;
	SDL_Window* mDisplayWindow;
	SDL_GLContext mGlContext;
};

