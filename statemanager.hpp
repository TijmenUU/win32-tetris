#pragma once
#include "eventhandler.hpp"
#include <memory>
#include "states/basestate.hpp"

class StateManager
{
private:
	std::vector<std::unique_ptr<State>> states;

	StateManager() = default;
	~StateManager() = default;
public:
	void Update(unsigned const elapsedMs);

	void PushState(std::unique_ptr<State>&& state);
	void PopState();
	std::size_t StateCount() const;

	static StateManager & GetInstance();
};

