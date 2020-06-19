#pragma once


#include "Common.hpp"
#include "Worker.h"
#include "IGuiDebug.h"
#include "IDrawable.h"
#include "IUpdateble.h"



class WorkersUnion : public IGuiDebug, public IDrawable, public IUpdateble
{
public:
	WorkersUnion();
	~WorkersUnion();

	void renderGuiDebug();
	void draw();
	void update(float ticks);

	void createNewWorker();
	std::shared_ptr<Worker> getIdleWorker();
	void returnWorker(std::shared_ptr<Worker> worker);

	std::vector<std::shared_ptr<Worker>> mIdleWorkers;
	std::vector<std::shared_ptr<Worker>> mWorkingWorkers;

};