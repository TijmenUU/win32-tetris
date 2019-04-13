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

	friend class Core;
	void ClearState();
	void Update();

	EventHandler();
	~EventHandler();

public:
	bool DidWindowResize() const;
	bool WasThereAnyAction() const;
	bool WasActionPressed(PlayerActions const action) const;
	bool WasActionReleased(PlayerActions const action) const;

	static EventHandler & GetInstance();
};

