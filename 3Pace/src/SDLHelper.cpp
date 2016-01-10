#include "SDLHelper.h"

constexpr SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;


SDLHelper::SDLHelper() {

}

bool SDLHelper::init(std::string title, int x, int y, int w, int h) {
	m_FPS = 0.0f;
	m_Delta = 0.0f;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		return false;

	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE))
		return false;
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3))
		return false;
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3))
		return false;

	// Create Window
	mDisplayWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (mDisplayWindow == nullptr)
		return false;

	// Get Window Context
	mGlContext = SDL_GL_CreateContext(mDisplayWindow);
	if (mGlContext == nullptr)
		return false;

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return false;

	// Hack: glewExperimental _sometimes_ sets the error flag (0x500). Read glGetError() one time to discard this error
	// https://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW_.28OpenGL_Extension_Wrangler.29
	glGetError();


	// Mouse movement relative
	SDL_SetRelativeMouseMode(SDL_TRUE);

	if (SDL_GL_SetSwapInterval(1) < 0)
		return false;

	initOpenGL();

	return true;
}

void SDLHelper::initOpenGL() {
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Set clear color to  black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void SDLHelper::printError() {
	// Print OpenGL errors
	GLenum err = GL_NO_ERROR;
	if ((err = glGetError()) != GL_NO_ERROR)
		std::cout << "ERROR: " << std::to_string(err) << std::endl;
}

void SDLHelper::calcFPS() {
	static GLfloat fps_lastTime = (GLfloat)SDL_GetTicks(), delta_lastTime = (GLfloat)SDL_GetTicks(), fps_frames = 0.0f;

	fps_frames++;
	m_Delta = 0.75f*m_Delta + 0.25f * ((GLfloat)SDL_GetTicks() - (GLfloat)delta_lastTime) / 1000.0f;
	delta_lastTime = (GLfloat)SDL_GetTicks();

	if (fps_lastTime < SDL_GetTicks() - 1000.0f) {
		fps_lastTime = (GLfloat)SDL_GetTicks();
		if (m_FPS == 0.0f)
			m_FPS = fps_frames;
		else
			m_FPS = m_FPS*0.75f + 0.25f*fps_frames;
		fps_frames = 0;
	}
}

GLfloat SDLHelper::getDelta() {
	return m_Delta;
}

GLfloat SDLHelper::getFPS() {
	return m_FPS;
}

SDL_Window* SDLHelper::getDisplayWindow() {
	return mDisplayWindow;
}

SDLHelper::~SDLHelper() {
	SDL_DestroyWindow(mDisplayWindow);
	SDL_GL_DeleteContext(mGlContext);
	SDL_Quit();
}
