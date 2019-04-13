#include <algorithm>
#include "world.hpp"
#include <thread>

int main()
{
	long long targetFrameTime = 100;
	World world;

	while (world.IsPlaying())
	{
		auto const start = std::chrono::steady_clock::now();

		world.Tick();

		auto const elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(start - std::chrono::steady_clock::now());
		std::this_thread::sleep_for(std::chrono::milliseconds(std::max(0LL, targetFrameTime - elapsed.count())));
	}

	return 0;
}