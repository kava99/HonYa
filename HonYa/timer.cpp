#include "timer.h"

Timer::Timer()
{
	m_time_passed = 0.0f;
}

Timer::~Timer()
{
}

void Timer::reset(float start_time)
{
	m_time_passed = start_time;
}

void Timer::update(float ticks)
{
	m_time_passed += ticks;
}

float Timer::time_passed()
{
	return m_time_passed;
}
