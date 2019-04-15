#include "../config.hpp"
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

PauseState::PauseState()
	: MessageState(
		COORD{ Config::playingFieldPosition.X, Config::playingFieldPosition.Y + (Config::playingFieldSize.Y / 2) },
		Config::playingFieldSize.X,
		"Game is paused",
		Color::Color(Color::Foreground::WHITE, Color::Background::BLUE))
{
}

PauseState::~PauseState()
{
}
