#pragma once

class State
{
public:
	virtual void Update(unsigned const elapsedMs) = 0;
	virtual void Awake() = 0;

	virtual ~State() = default;
};

