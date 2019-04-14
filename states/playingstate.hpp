#pragma once
#include "../game/field.hpp";
#include "basestate.hpp"

class PlayingState : public State
{
private:
	Game::Field field;

	void Pause();

	void HandleInput(EventHandler const & evHandler);

	void DrawStatics() const;
	void DrawDynamics() const;
	// TODO pause line field refresh logic

public:
	void Update(unsigned const elapsedMs) override;
	void Awake() override;

	PlayingState();
	~PlayingState();
};

