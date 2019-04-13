#pragma once
#include "basestate.hpp"

class PlayingState : public State
{
private:
	bool CheckWindowSize();
	void Pause();

	void HandleInput(EventHandler const & evHandler);

	void DrawStatics() const;
	void DrawDynamics() const;

public:
	void Update(unsigned const elapsedMs) override;
	void Awake() override;

	PlayingState();
	~PlayingState();
};

