#include "../config.hpp"
#include "../conutils/color.hpp"
#include "../conutils/coordops.hpp"
#include "../conutils/cursor.hpp"
#include "../conutils/window.hpp"
#include "../statemanager.hpp"
#include "playingstate.hpp"
#include "pausestate.hpp"

void PlayingState::Pause()
{
	StateManager& stManager = StateManager::GetInstance();
	stManager.PushState(std::make_unique<PauseState>());
}

void PlayingState::HandleInput(EventHandler const& evHandler)
{
	if (evHandler.WasActionReleased(PlayerActions::Pause))
	{
		Pause();
		return;
	}
}

void PlayingState::DrawGUI() const
{
	std::cout << Color::Color(); // Black and white

	/* SCORE LABEL */
	Cursor::Set({ Config::scorePosition.X, Config::scorePosition.Y - 1});
	std::cout << "SCORE:";

	/* PREVIEW BLOCK LABEL */
	Cursor::Set({ Config::previewTetrominoPosition.X, Config::previewTetrominoPosition.Y - 1 });
	std::cout << "NEXT:";

	/* BORDERING */
	Color::Set(Color::Color(static_cast<std::uint8_t>(Color::Background::LIGHTGRAY)));
	char const borderChar = '#';
	// Top and bottom
	for (SHORT x = Config::playingFieldPosition.X - 1; x < Config::playingFieldPosition.X + Config::playingFieldSize.X + 1; ++x)
	{
		Cursor::Set({ x, static_cast<SHORT>(Config::playingFieldPosition.Y - 1) });
		std::cout << borderChar;

		Cursor::Set({ x, static_cast<SHORT>(Config::playingFieldPosition.Y + Config::playingFieldSize.Y) });
		std::cout << borderChar;
	}

	// Sides
	for (SHORT y = Config::playingFieldPosition.Y; y < Config::playingFieldPosition.Y + Config::playingFieldSize.Y; ++y)
	{
		Cursor::Set({ static_cast<SHORT>(Config::playingFieldPosition.X - 1), y });
		std::cout << borderChar;
		Cursor::Set({ Config::playingFieldPosition.X + Config::playingFieldSize.X, y });
		std::cout << borderChar;
	}
}

void PlayingState::Update(unsigned const elapsedMs)
{
	EventHandler& evHandler = EventHandler::GetInstance();
	if (evHandler.WasThereAnyAction())
	{
		HandleInput(evHandler);
	}

	player.Update(elapsedMs);
}

void PlayingState::Awake()
{
	
}

PlayingState::PlayingState()
	: field(Config::playingFieldPosition, Config::playingFieldSize),
	player(Config::previewTetrominoPosition, Config::scorePosition, field)
{
	DrawGUI();
}

PlayingState::~PlayingState()
{
}
