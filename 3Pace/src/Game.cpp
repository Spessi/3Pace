#include "Game.h"

Game::Game() {

}

Game::~Game() {
	delete m_World;
}

bool Game::init(int w, int h) {
	// Create new OpenGL Window
	std::unique_ptr<SDLHelper> SDLOGL_Helper(new SDLHelper());
	SDLOGL_Helper->init("3Pace", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h);
	
	// Create new world
	m_World = new World();
	m_World->init();
	resize(w, h);

	m_Running = true;

	// Start game loop
	while (m_Running) {
		SDLOGL_Helper->calcFPS();
		SDL_SetWindowTitle(SDLOGL_Helper->getDisplayWindow(), std::string("FPS: " + std::to_string(SDLOGL_Helper->getFPS()) + " | dt: " + std::to_string(SDLOGL_Helper->getDelta())).c_str());
		handleEvents();

		m_World->process(SDLOGL_Helper->getDelta());

		// Print error if existent
		SDLOGL_Helper->printError();

		// Swap display buffers
		SDL_GL_SwapWindow(SDLOGL_Helper->getDisplayWindow());
	}

	return false;
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.event) {
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				std::cout << "Width: " << event.window.data1 << " | Height: " << event.window.data2 << std::endl;
				resize(event.window.data1, event.window.data2);
				break;
			}
		}
		else if (event.type == SDL_QUIT) {
			m_Running = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			SDL_Keycode key = event.key.keysym.sym;

			if (key == SDLK_ESCAPE)
				m_Running = false;
		}
	}
}

void Game::resize(int w, int h) {
	m_World->getCamera()->setAspectRatio((float)w / (float)h);
}

World* Game::getWorld() {
	return m_World;
}
