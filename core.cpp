#include "config.hpp"
#include "core.hpp"
#include "states/playingstate.hpp"
#include <thread>
#include <Windows.h>

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
	// Setup the console screen
	HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND windowHandle = GetConsoleWindow();
	// Set the console to a fixed size
	SetConsoleScreenBufferSize(stdoutHandle, Config::consoleBufferSize);
	
	SMALL_RECT s_rect{
		0,
		0,
		Config::consoleBufferSize.X,
		Config::consoleBufferSize.Y
	};
	// Reset any scroll
	if (SetConsoleWindowInfo(stdoutHandle, true, &s_rect))
	{
		// Set the actual window size
		WINDOWINFO windowInfo;
		memset(&windowInfo, 0, sizeof(WINDOWINFO));
		if (GetWindowInfo(windowHandle, &windowInfo))
		{
			MoveWindow(
				windowHandle,
				windowInfo.rcWindow.left,
				windowInfo.rcWindow.top,
				Config::windowSize.X,
				Config::windowSize.Y,
				true);
		}
	}

	// Turn off the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(stdoutHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(stdoutHandle, &cursorInfo);
}

Core::~Core()
{
}
