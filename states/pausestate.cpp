#include "../eventhandler.hpp"
#include "../statemanager.hpp"
#include "pausestate.hpp"

void PauseState::Update(unsigned const elapsedMs)
{
	EventHandler& evHandler = EventHandler::GetInstance();
	if (evHandler.WasActionReleased(PlayerActions::Pause))
	{
		StateManager::GetInstance().PopState();
		return;
	}
	if (evHandler.WasActionReleased(PlayerActions::Escape))
	{
		StateManager::GetInstance().PopState();
		return;
	}
}

PauseState::PauseState(
	COORD const _lineStartPosition,
	SHORT const _maxLineLength)
	: MessageState(
		_lineStartPosition,
		_maxLineLength,
		"Game is paused",
		Color::Color(Color::Foreground::WHITE, Color::Background::BLUE))
{
}

PauseState::~PauseState()
{
}
