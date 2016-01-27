#include <iostream>
#include <memory>
#include "Game.h"

// Interrupt/Sleep //
#include <chrono>  //
#include <thread>  //
/////////////////////

int main() {
	/*while (1) {

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}*/

	Game game;
	game.init(1280, 720);

	return 0;
}