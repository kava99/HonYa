#pragma once

#include "Common.hpp"
#include "IUpdateble.h"

class Timer : public IUpdateble
{
public:
	Timer();
	~Timer();

	void reset(float startTime = 0.0f);
	void update(float ticks);
	float timePassed();

private:
	float mTimePassed;
};

