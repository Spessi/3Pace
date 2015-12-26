#include "SDLHelper.h"

constexpr SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;

GLuint vertexbuffer;
SDLHelper::SDLHelper(std::string title, int x, int y, int w, int h) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error(std::string("Couldn't initialize SDL: ") + std::string(SDL_GetError()));
	
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw std::runtime_error("Couldn't initialize SDL2 Image: " + std::string(SDL_GetError()));

	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE))
		throw std::runtime_error("Couldn't set OpenGL profile mask: " + std::string(SDL_GetError()));
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3))
		throw std::runtime_error("Couldn't set OpenGL major version: " + std::string(SDL_GetError()));
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2))
		throw std::runtime_error("Couldn't set OpenGL minor version: " + std::string(SDL_GetError()));

	// Create Window
	mDisplayWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_OPENGL);
	if (mDisplayWindow == nullptr)
		throw std::runtime_error("Couldn't create window: " + std::string(SDL_GetError()));

	// Get Window Context
	mGlContext = SDL_GL_CreateContext(mDisplayWindow);
	if (mGlContext == nullptr)
		throw std::runtime_error("Couldn't create display context: " + std::string(SDL_GetError()));

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Couldn't initialize GLEW");

	if (SDL_GL_SetSwapInterval(1) < 0)
		throw std::runtime_error("Couldn't enable VSync");

	// Create program object to bind shaders on it
	if ((mProgramID = glCreateProgram()) == 0)
		throw std::runtime_error("Couldn't create OpenGL program object");

	mRunning = true;
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void SDLHelper::loop() {
	SDL_Event event;

	while (mRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				mRunning = false;
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Render
		// todo...
		// Render End
		SDL_GL_SwapWindow(mDisplayWindow);
	}
}

SDLHelper::~SDLHelper() {
	SDL_DestroyWindow(mDisplayWindow);
	SDL_GL_DeleteContext(mGlContext);
	SDL_Quit();
}
