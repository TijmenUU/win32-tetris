#pragma once
#include "eventhandler.hpp"
#include <tuple>
#define NOMINMAX
#include <Windows.h>

class World
{
private:
	COORD windowSize;
	EventHandler evHandler;

	enum class State
	{
		Paused,
		WrongWindowSize,
		Playing,
		Closing
	};
	State state;

	void UpdateWindowSize();
	void SetPauseGame(bool const pause = true);

	void HandleInput();
	void HandleResize();
	void Update();
	void DrawMessage(std::string msg);
	void DrawStatics();
	void Draw();

public:
	void Tick();

	bool IsPlaying() const;

	World();
	~World();
};

