#include "conutils/coordops.hpp"
#include "conutils/cursor.hpp"
#include "conutils/window.hpp"
#include "world.hpp"

COORD const minWindowSize{ 32, 30 };
COORD const playingFieldPosition{ 1, 1 };
COORD const playingFieldSize{ 28, 28 };

void World::UpdateWindowSize()
{
	auto const window = Window::ActiveViewport();
	windowSize = window.bottomRight - window.topLeft;
	if (windowSize.X >= minWindowSize.X && windowSize.Y >= minWindowSize.Y)
	{
		state = State::Playing;
		SetPauseGame(true);
	}
	else
	{
		state = State::WrongWindowSize;
		DrawMessage("Window size is NOT OK");
	}
}

void World::SetPauseGame(bool const pause)
{
	if (pause && state == State::Playing)
	{
		state = State::Paused;
		DrawMessage("Game is Paused");
	}
	else if (!pause && state == State::Paused)
	{
		state = State::Playing;
		DrawMessage("");// DEBUG
	}
}

void World::HandleInput()
{
	if (evHandler.WasActionReleased(PlayerActions::Pause))
	{
		SetPauseGame(state == State::Playing);
	}
}

void World::HandleResize()
{
	UpdateWindowSize();
	DrawStatics();
}

void World::Update()
{
}

void World::DrawMessage(std::string msg)
{
	if (msg.size() > playingFieldSize.X)
	{
		msg.resize(static_cast<unsigned>(playingFieldSize.X));
	}

	SHORT const x = (playingFieldSize.X / 2) - (msg.size() / 2) + playingFieldPosition.X;
	SHORT const y = playingFieldSize.Y / 2 + playingFieldPosition.Y;
	// TODO use color?
	Cursor::Set({ playingFieldPosition.X, y });
	for (SHORT i = playingFieldPosition.X; i < x; ++i)
		std::cout << ' ';
	std::cout << msg;
	for (SHORT i = x + msg.size(); i < playingFieldPosition.X + playingFieldSize.X; ++i)
		std::cout << ' ';
}

void World::DrawStatics()
{
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

void World::Draw()
{
	if (state == State::Playing)
	{
		// Draw the dynamic things
	}
}

void World::Tick()
{
	evHandler.Update();
	if(evHandler.WasThereAnyAction())
		HandleInput();
	if(evHandler.DidWindowResize())
		HandleResize();
	Update();
	Draw();
}

bool World::IsPlaying() const
{
	return state != State::Closing;
}

World::World()
	: windowSize({0, 0}),
	state(State::Paused)
{
	HandleResize();
}

World::~World()
{
}
