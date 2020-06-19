#include "Timer.h"

Timer::Timer()
{
	mTimePassed = 0.0f;
}

Timer::~Timer()
{
}

void Timer::reset(float startTime)
{
	mTimePassed = startTime;
}

void Timer::update(float ticks)
{
	mTimePassed += ticks;
}

float Timer::timePassed()
{
	return mTimePassed;
}
