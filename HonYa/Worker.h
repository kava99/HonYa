#pragma once


#include "Common.hpp"
#include "GraphicsEngine.h"

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


class Worker
{
public:
	Worker();
	~Worker();

	void draw();

	vec2 mPosition;
	TaskType mTaskType;

	ALLEGRO_BITMAP* bball;


};