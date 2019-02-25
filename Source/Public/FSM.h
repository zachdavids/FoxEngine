#pragma once

#include <deque>
#include <map>
#include <functional>
#include <iostream>

class FSM
{
public:
	FSM();
	void Update();
	void PushState(std::function<void()> function);
	void PopState();
	std::function<void()> GetState();
private:
	std::deque<std::function<void()>> states_;
};