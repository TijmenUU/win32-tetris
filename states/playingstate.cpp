#include "../conutils/color.hpp"
#include "../conutils/coordops.hpp"
#include "../conutils/cursor.hpp"
#include "../conutils/window.hpp"
#include "../statemanager.hpp"
#include "playingstate.hpp"
#include "pausestate.hpp"

COORD const playingFieldPosition{ 1, 1 };
COORD const playingFieldSize{ 28, 28 };
COORD const scorePosition{ playingFieldPosition.X + playingFieldSize.X + 2, 2 };

COORD GetMessageCoordinate()
{
	return COORD({playingFieldPosition.X, playingFieldPosition.Y + (playingFieldSize.Y / 2)});
}

void PlayingState::Pause()
{
	StateManager& const stManager = StateManager::GetInstance();
	stManager.PushState(std::make_unique<PauseState>(GetMessageCoordinate(), playingFieldSize.X));
}

void PlayingState::HandleInput(EventHandler const& evHandler)
{
	if (evHandler.WasActionReleased(PlayerActions::Escape))
	{
		StateManager::GetInstance().PopState();
		return;
	}
	if (evHandler.WasActionReleased(PlayerActions::Pause))
	{
		Pause();
		return;
	}
}

void PlayingState::DrawStatics() const
{
	/* Clear everything */
	auto const window = Window::GetActiveViewportSize();
	Cursor::Set({ 0, 0 });
	std::cout << Color::Color(); // Black and white
	for (SHORT y = 0; y < window.bottomRight.Y; ++y)
	{
		for (SHORT x = 0; x < window.bottomRight.X; ++x)
		{
			std::cout << ' '; 
		}
	}

	/* SCORE LABEL */
	Cursor::Set({ scorePosition.X, scorePosition.Y - 1});
	std::cout << "SCORE:";

	/* BORDERING */
	char const borderChar = '#';
	// Top and bottom
	for (SHORT x = playingFieldPosition.X - 1U; x < playingFieldPosition.X + playingFieldSize.X + 1U; ++x)
	{
		Cursor::Set({ x, static_cast<SHORT>(playingFieldPosition.Y - 1U) });
		std::cout << borderChar;

		Cursor::Set({ x, static_cast<SHORT>(playingFieldPosition.Y + playingFieldSize.Y) });
		std::cout << borderChar;
	}

	// Sides
	for (SHORT y = playingFieldPosition.Y; y < playingFieldPosition.Y + playingFieldSize.Y; ++y)
	{
		Cursor::Set({ static_cast<SHORT>(playingFieldPosition.X - 1U), y });
		std::cout << borderChar;
		Cursor::Set({ playingFieldPosition.X + playingFieldSize.X, y });
		std::cout << borderChar;
	}
}

void PlayingState::DrawDynamics() const
{
	field.Draw();
}

void PlayingState::Update(unsigned const elapsedMs)
{
	DrawDynamics();

	EventHandler& evHandler = EventHandler::GetInstance();
	if (evHandler.WasThereAnyAction())
	{
		HandleInput(evHandler);
	}
	field.Update(elapsedMs);
}

void PlayingState::Awake()
{
	DrawStatics();
}

PlayingState::PlayingState()
	: field(playingFieldPosition, playingFieldSize)
{
}

PlayingState::~PlayingState()
{
}
