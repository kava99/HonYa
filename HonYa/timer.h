#pragma once

#include "common.h"

class Timer
{
public:
	Timer();
	~Timer();

	void reset(float start_time = 0.0f);
	void update(float ticks);
	float time_passed();

private:
	float m_time_passed;
};

