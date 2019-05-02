#pragma once
#include <unordered_set>

enum class PlayerActions
{
	Escape,
	MoveDown,
	MoveLeft,
	MoveRight,
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

	friend class Game;
	void ClearState();
	void Update();

	EventHandler() = default;
	~EventHandler() = default;

public:
	bool WasThereAnyAction() const;
	bool WasActionPressed(PlayerActions const action) const;
	bool WasActionReleased(PlayerActions const action) const;

	static EventHandler & GetInstance();
};

