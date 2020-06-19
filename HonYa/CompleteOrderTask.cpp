#include "CompleteOrderTask.h"

CompleteOrderTask::CompleteOrderTask()
{
	mOrder = nullptr;
	mMagazine = nullptr;
	mAssignedWorker = nullptr;
	mIsFinished = false;
}

CompleteOrderTask::~CompleteOrderTask()
{
}

void CompleteOrderTask::update(float ticks)
{
	if (mMagazine == nullptr || mOrder == nullptr || mAssignedWorker == nullptr) return;

	auto shelf = mMagazine->getObjectByItem(mOrder->mBookIds[0]);

	vec2 posOfBook = { shelf->mPosition.x, shelf->mPosition.y };
	mAssignedWorker->mDestination = posOfBook;

	if (mAssignedWorker->mPosition.x == posOfBook.x
		&& mAssignedWorker->mPosition.y == posOfBook.y) {
		mMagazine->withdrawItemFromObject(mOrder->mBookIds[0], shelf->mUniqueId);
		mIsFinished = true;

	}


}

void CompleteOrderTask::assignWorker(std::shared_ptr<Worker> worker)
{
	if (worker == nullptr)return;
	
	mAssignedWorker = worker;
	mAssignedWorker->mTaskType = TaskType::COMPLETE_ORDER;
}
