#pragma once


#include "Common.hpp"
#include "GraphicsEngine.h"
#include "IDrawable.h"
#include "IUpdateble.h"

enum class TaskType : int {
	IDLE,
	COMPLETE_ORDER,
};

static std::map<TaskType, std::string> taskTypeString{
		{ TaskType::IDLE, "IDLE" },
		{ TaskType::COMPLETE_ORDER, "COMPLETE ORDER" },
};

static std::string taskString[] = {
	"Idle",
	"Complete order",
};


class Worker : public IDrawable, public IUpdateble
{
public:
	Worker();
	~Worker();

	void draw();
	void update(float ticks);

	vec2 mPosition;
	vec2 mDestination;
	TaskType mTaskType;

	float mSpeed;

	ALLEGRO_BITMAP* bball;


};