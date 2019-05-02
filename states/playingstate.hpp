#pragma once
#include "../entity/field.hpp"
#include "../entity/player.hpp"
#include "basestate.hpp"

class PlayingState : public State
{
private:
	Entity::Field field;
	Entity::Player player;

	void Pause();

	void HandleInput(UserInput const & evHandler);

	void DrawGUI() const;

public:
	void Update(unsigned const elapsedMs) override;
	void Awake() override;

	PlayingState();
	~PlayingState();
};

