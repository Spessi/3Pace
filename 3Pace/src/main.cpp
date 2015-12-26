#include <iostream>
#include <memory>
#include "SDLHelper.h"
#include "Heightmap.h"


int main() {

	Heightmap* heightmap = new Heightmap("blah");

	try {
		std::unique_ptr<SDLHelper> helper(new SDLHelper("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512));
		helper->loop();
	}
	catch (std::exception e) {
		std::cout << "Exception: " << e.what() << std::endl;
		return -1;
	}
	

	return 0;
}