#include <algorithm>
#include "game.hpp"
#include <thread>

int main()
{
	Game game;

	unsigned const targetFrameTime = 16; // 60 FPS
	game.Run(targetFrameTime);

	return 0;
}