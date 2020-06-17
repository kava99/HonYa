#pragma once


#include "Common.hpp"
#include "Worker.h"
#include "IGuiDebug.h"
#include "IDrawable.h"



class WorkersUnion : public IGuiDebug, public IDrawable
{
public:
	WorkersUnion();
	~WorkersUnion();

	void renderGuiDebug();
	void draw();

	void createNewWorker();
	std::shared_ptr<Worker> getIdleWorker();
	void returnWorker(std::shared_ptr<Worker> worker);

	std::vector<std::shared_ptr<Worker>> mIdleWorkers;
	std::vector<std::shared_ptr<Worker>> mWorkingWorkers;

};