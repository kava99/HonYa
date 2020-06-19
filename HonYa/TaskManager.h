#pragma once

#include "Common.hpp"
#include "CompleteOrderTask.h"
#include "IUpdateble.h"
#include "WorkersUnion.h"


class TaskManager : public IUpdateble
{
	static TaskManager* ms_instance;

public:
	static TaskManager* Instance();
	static void Release();

	void update(float ticks);
	void checkAvailableWorkers();


	std::shared_ptr<Magazine> mMagazine;
	std::shared_ptr<WorkersUnion> mWorkersUnion;
	void pushOrderCompletionTask(std::shared_ptr<Order> order);
	void popOrderCompletionTask(std::shared_ptr<CompleteOrderTask> cot);


private:
	std::vector<std::shared_ptr<CompleteOrderTask>> mOrderCompletionTaskQueue;
	std::vector<std::shared_ptr<CompleteOrderTask>> mOrderCompletionTasksWithoutWorkers;

	TaskManager();
	~TaskManager();
};

