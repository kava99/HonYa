#include "TaskManager.h"

TaskManager* TaskManager::ms_instance = nullptr;

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
}

TaskManager* TaskManager::Instance()
{
	if (ms_instance == nullptr) {
		ms_instance = new TaskManager();
	}
	return ms_instance;
}

void TaskManager::Release()
{
	if (ms_instance) {
		delete ms_instance;
	}
	ms_instance = nullptr;
}

void TaskManager::update(float ticks)
{
	checkAvailableWorkers();
	int i = 0;
	for (auto& cot : mOrderCompletionTaskQueue) {
		cot->update(ticks);
		if (cot->isFinished()) {
			cot->mOrder->mIsCompleted = true;
			popOrderCompletionTask(cot);
			break;
		}
	}
}

void TaskManager::checkAvailableWorkers()
{


	if (mWorkersUnion->mIdleWorkers.size() == 0) return;
	if (mOrderCompletionTasksWithoutWorkers.size() == 0) return;

	auto cot = mOrderCompletionTasksWithoutWorkers.back();


	cot->assignWorker(mWorkersUnion->getIdleWorker());
	mOrderCompletionTaskQueue.push_back(cot);

	mOrderCompletionTasksWithoutWorkers.pop_back();

}

void TaskManager::pushOrderCompletionTask(std::shared_ptr<Order> order)
{
	if (mMagazine == nullptr || mWorkersUnion == nullptr) {
		std::cout << "Cannot push task! No Magazine or WorkersUnion assigned\n";
		return;
	}

	std::shared_ptr<CompleteOrderTask> cot = std::make_shared<CompleteOrderTask>();
	cot->mMagazine = mMagazine;
	cot->mOrder = order;
	mOrderCompletionTasksWithoutWorkers.push_back(cot);

}

void TaskManager::popOrderCompletionTask(std::shared_ptr<CompleteOrderTask> cot)
{
	mWorkersUnion->returnWorker(cot->mAssignedWorker);
	mOrderCompletionTaskQueue.erase(std::remove(mOrderCompletionTaskQueue.begin(), mOrderCompletionTaskQueue.end(), cot), mOrderCompletionTaskQueue.end());
}
