#include "FSM.h"

FSM::FSM()
{
}

void FSM::Update()
{
	if (states_.size() != 0)
	{
		states_.front()();
	}
}

void FSM::PopState()
{
	states_.pop_front();
}

std::function<void()> FSM::GetState()
{
	return states_.front();
}

void FSM::PushState(std::function<void()> function)
{
	states_.push_back(function);
}
