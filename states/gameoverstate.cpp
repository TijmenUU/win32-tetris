#include "../config.hpp"
#include "../eventhandler.hpp"
#include "../statemanager.hpp"
#include "gameoverstate.hpp"
#include "playingstate.hpp"

void GameOverState::Update(unsigned const elapsedMs)
{
	auto& evHandler = EventHandler::GetInstance();

	if (evHandler.WasActionReleased(PlayerActions::Yes))
	{
		auto& stManager = StateManager::GetInstance();
		stManager.PopState();
		stManager.PushState(std::make_unique<PlayingState>());
		return;
	}
	else if (evHandler.WasActionReleased(PlayerActions::No))
	{
		auto& stManager = StateManager::GetInstance();
		stManager.PopState();
		return;
	}
}

GameOverState::GameOverState()
	: MessageState(
		COORD{Config::playingFieldPosition.X, Config::playingFieldPosition.Y + Config::playingFieldSize.Y / 2},
		Config::playingFieldSize.X,
		"Game Over! Continue? Y/N",
		Color::Color(Color::Foreground::WHITE, Color::Background::DARKRED))
{
}

GameOverState::~GameOverState()
{
}
