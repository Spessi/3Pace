#pragma once
#include <SDL.h>
#include <SDL_image.h>
#undef main
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

// Developing....
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
};

class SDLHelper {
public:
	SDLHelper();
	~SDLHelper();
	bool init(std::string title, int x, int y, int w, int h);
	SDL_Window* getDisplayWindow();
	void printError();
	void calcFPS();
	GLfloat getFPS();
	GLfloat getDelta();

private:
	SDL_Window* mDisplayWindow;
	SDL_GLContext mGlContext;
	GLfloat m_FPS;
	GLfloat m_Delta;

	void initOpenGL();
};

