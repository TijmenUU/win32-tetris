#include <algorithm>
#include "core.hpp"
#include <thread>

int main()
{
	Core core;

	unsigned const targetFrameTime = 16; // 60 FPS
	core.Run(targetFrameTime);

	return 0;
}