#include "core.hpp"
#include "states/playingstate.hpp"
#include <thread>

void Core::Run(unsigned const targetFrameTime)
{
	StateManager& const stManager = StateManager::GetInstance();
	stManager.PushState(std::make_unique<PlayingState>());

	EventHandler& const evHandler = EventHandler::GetInstance();
	while (stManager.StateCount())
	{
		auto const start = std::chrono::steady_clock::now();

		evHandler.Update();
		stManager.Update(targetFrameTime);

		auto const sleepTime = targetFrameTime - std::chrono::duration_cast<std::chrono::milliseconds>(start - std::chrono::steady_clock::now()).count();
		if (sleepTime > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
		}
	}
}

Core::Core()
{
}

Core::~Core()
{
}
