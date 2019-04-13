#pragma once
#include <unordered_set>

enum class PlayerActions
{
	Escape,
	MoveDown,
	RotateLeft,
	RotateRight,
	Pause,
	Yes,
	No
};

class EventHandler
{
private:
	std::unordered_set<PlayerActions> playerActionPresses;
	std::unordered_set<PlayerActions> playerActionReleases;
	bool didWindowResize;

	void ClearState();

public:
	void Update();

	bool DidWindowResize() const;
	bool WasThereAnyAction() const;
	bool WasActionPressed(PlayerActions const action) const;
	bool WasActionReleased(PlayerActions const action) const;

	EventHandler();
	~EventHandler();
};

