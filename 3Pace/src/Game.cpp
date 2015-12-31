#include "Game.h"

Game::Game(int w, int h) {
	// Create new OpenGL Window
	std::unique_ptr<SDLHelper> SDLOGL_Helper(new SDLHelper("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h));

	// Create new world
	m_World = new World();
	resize(w, h);

	m_Running = true;

	// Start game loop
	while (m_Running) {
		SDLOGL_Helper->calcFPS();
		SDL_SetWindowTitle(SDLOGL_Helper->getDisplayWindow(), std::string("FPS: " + std::to_string(SDLOGL_Helper->getFPS()) + " | dt: " + std::to_string(SDLOGL_Helper->getDelta())).c_str());
		handleEvents();

		m_World->process(SDLOGL_Helper->getDelta());

		// Print error if existant
		SDLOGL_Helper->printError();
	}
}

Game::~Game() {
	delete m_World;
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
			else
				m_World->processKeyboard(event.key.keysym.sym);
		}
	}
}

void Game::resize(int w, int h) {
	m_World->setProjectionMatrix(glm::perspective(glm::radians(45.0f), (float)w/(float)h, 0.1f, 100.0f));
}

World* Game::getWorld() {
	return m_World;
}
