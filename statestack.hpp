#pragma once
#include "eventhandler.hpp"
#include <memory>
#include "states/basestate.hpp"

class StateStack
{
private:
	std::vector<std::unique_ptr<State>> states;

	StateStack() = default;
	~StateStack() = default;

public:
	void PushState(std::unique_ptr<State>&& state);
	void PopState();
	std::size_t StateCount() const;
	State* const GetTopState();

	static StateStack & GetInstance();
};

