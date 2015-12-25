#include <iostream>
#include <memory>
#include "SDLHelper.h"



int main() {
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