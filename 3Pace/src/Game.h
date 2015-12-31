#pragma once

#include <memory>
#include "World.h"
#include "SDLHelper.h"

class Game {
public:
	Game(int w, int h);
	~Game();
	World* getWorld();

private:
	bool m_Running;
	World* m_World;
	void handleEvents();
	void resize(int w, int h);
};

