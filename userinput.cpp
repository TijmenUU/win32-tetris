#include "conutils/event.hpp"
#include "userinput.hpp"

void UserInput::ClearState()
{
	playerActionPresses.clear();
	playerActionReleases.clear();
}

void UserInput::Update()
{
	unsigned const bufferSize = 64;
	std::vector<Event::InputEvent> buffer;
	buffer.resize(bufferSize);

	Event::GetAll(buffer); // TODO check if we ever get more than 64 events per call

	ClearState();

	for (auto ev : buffer)
	{
		switch (ev.GetEventType())
		{
		case Event::Type::KEY:
			// https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes
			switch (ev.Event.KeyEvent.wVirtualKeyCode)
			{
			case VK_ESCAPE:
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::Escape);
				else
					playerActionReleases.insert(PlayerActions::Escape);
				break;
			case 0x53: // S
				if(ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::MoveDown);
				else
					playerActionReleases.insert(PlayerActions::MoveDown);
				break;
			case 0x41: // A
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::MoveLeft);
				else
					playerActionReleases.insert(PlayerActions::MoveLeft);
				break;
			case 0x44: // D
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::MoveRight);
				else
					playerActionReleases.insert(PlayerActions::MoveRight);
				break;
			case 0x51: // Q
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::RotateLeft);
				else
					playerActionReleases.insert(PlayerActions::RotateLeft);
				break;
			case 0x45: // E
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::RotateRight);
				else
					playerActionReleases.insert(PlayerActions::RotateRight);
				break;
			case 0x50: // P
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::Pause);
				else
					playerActionReleases.insert(PlayerActions::Pause);
				break;
			case 0x59: // Y
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::Yes);
				else
					playerActionReleases.insert(PlayerActions::Yes);
				break;
			case 0x4E: // N
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::No);
				else
					playerActionReleases.insert(PlayerActions::No);
				break;
			}
			break;
		default:
			break;
		}
	}
}

bool UserInput::WasThereAnyAction() const
{
	return !(playerActionPresses.empty() && playerActionReleases.empty());
}

bool UserInput::WasActionPressed(PlayerActions const action) const
{
	if (playerActionPresses.find(action) == playerActionPresses.end())
	{
		return false;
	}

	return true;
}

bool UserInput::WasActionReleased(PlayerActions const action) const
{
	if (playerActionReleases.find(action) == playerActionReleases.end())
	{
		return false;
	}

	return true;
}

UserInput & UserInput::GetInstance()
{
	static UserInput evHandler;
	return evHandler;
}
