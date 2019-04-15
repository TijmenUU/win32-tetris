#include "conutils/event.hpp"
#include "eventhandler.hpp"

void EventHandler::ClearState()
{
	playerActionPresses.clear();
	playerActionReleases.clear();
	didWindowResize = false;
}

void EventHandler::Update()
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
			case VK_DOWN:
				if(ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::MoveDown);
				else
					playerActionReleases.insert(PlayerActions::MoveDown);
				break;
			case VK_LEFT:
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::MoveLeft);
				else
					playerActionReleases.insert(PlayerActions::MoveLeft);
				break;
			case VK_RIGHT:
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
		case Event::Type::RESIZE:
			didWindowResize = true;
			break;
		default:
			break;
		}
	}
}

bool EventHandler::DidWindowResize() const
{
	return didWindowResize;
}

bool EventHandler::WasThereAnyAction() const
{
	return !(playerActionPresses.empty() && playerActionReleases.empty());
}

bool EventHandler::WasActionPressed(PlayerActions const action) const
{
	if (playerActionPresses.find(action) == playerActionPresses.end())
	{
		return false;
	}

	return true;
}

bool EventHandler::WasActionReleased(PlayerActions const action) const
{
	if (playerActionReleases.find(action) == playerActionReleases.end())
	{
		return false;
	}

	return true;
}

EventHandler & EventHandler::GetInstance()
{
	static EventHandler evHandler;
	return evHandler;
}

EventHandler::EventHandler()
	: didWindowResize(false)
{
}

EventHandler::~EventHandler()
{
}
