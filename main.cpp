#include <algorithm>
#include "core.hpp"
#include <thread>

int main()
{
	Core core;

	unsigned const targetFrameTime = 100;
	core.Run(targetFrameTime);

	return 0;
}