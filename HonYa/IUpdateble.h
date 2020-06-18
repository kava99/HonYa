#pragma once


class IUpdateble
{
public:
	virtual ~IUpdateble() {};
	virtual void update(float ticks) = 0;

};
