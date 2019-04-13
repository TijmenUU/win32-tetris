#include <algorithm>
#include "conutils/coordops.hpp"
#include "conutils/cursor.hpp"
#include "conutils/window.hpp"
#include "statemanager.hpp"

void StateManager::Update(unsigned const elapsedMs)
{
	auto& state = states.back();
	state->Update(elapsedMs);
}

void StateManager::PushState(std::unique_ptr<State>&& state)
{
	states.emplace_back(std::move(state));
	states.back()->Awake();
}

void StateManager::PopState()
{
	states.pop_back();
	if (!states.empty())
	{
		states.back()->Awake();
	}
}

std::size_t StateManager::StateCount() const
{
	return states.size();
}

StateManager & StateManager::GetInstance()
{
	static StateManager stManager;

	return stManager;
}
