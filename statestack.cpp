#include <algorithm>
#include "conutils/coordops.hpp"
#include "conutils/cursor.hpp"
#include "conutils/window.hpp"
#include "statestack.hpp"

void StateStack::PushState(std::unique_ptr<State>&& state)
{
	states.emplace_back(std::move(state));
	states.back()->Awake();
}

void StateStack::PopState()
{
	states.pop_back();
	if (!states.empty())
	{
		states.back()->Awake();
	}
}

std::size_t StateStack::StateCount() const
{
	return states.size();
}

State* const StateStack::GetTopState()
{
	if (!states.empty())
	{
		return states.back().get();
	}

	return nullptr;
}

StateStack & StateStack::GetInstance()
{
	static StateStack stateStack;

	return stateStack;
}
