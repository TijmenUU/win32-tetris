#include "../conutils/coordops.hpp"
#include "../conutils/window.hpp"
#include "../statemanager.hpp"
#include "windowsizestate.hpp"

void WindowSizeState::Update(unsigned const elapsedMs)
{
	auto const window = Window::GetActiveViewportSize();
	auto const windowSize = window.bottomRight - window.topLeft;
	if (windowSize.X >= minWindowSize.X && windowSize.Y >= minWindowSize.Y)
	{
		StateManager::GetInstance().PopState();
		return;
	}
}

WindowSizeState::WindowSizeState(COORD const _lineStartPosition,
	SHORT const _maxLineLength,
	COORD const _minWindowSize)
	: MessageState(
		_lineStartPosition,
		_maxLineLength, 
		"Please enlarge the window",
		Color::Color(Color::Foreground::WHITE, Color::Background::DARKRED)),
	minWindowSize(_minWindowSize)
{
}

WindowSizeState::~WindowSizeState()
{
}
