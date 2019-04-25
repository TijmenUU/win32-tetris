#pragma once
#include "../game/field.hpp"
#include "../game/player.hpp"
#include "basestate.hpp"

class PlayingState : public State
{
private:
	Game::Field field;
	Game::Player player;

	void Pause();

	void HandleInput(EventHandler const & evHandler);

	void DrawGUI() const;

public:
	void Update(unsigned const elapsedMs) override;
	void Awake() override;

	PlayingState();
	~PlayingState();
};

