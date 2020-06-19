#pragma once

#include "IUpdateble.h"
#include "Order.h"
#include "Magazine.h"
#include "Worker.h"

class CompleteOrderTask : public IUpdateble
{
public:
	CompleteOrderTask();
	~CompleteOrderTask();

	void update(float ticks);

	std::shared_ptr<Order> mOrder;
	std::shared_ptr<Magazine> mMagazine;

	bool isFinished() { return mIsFinished; }
	std::shared_ptr<Worker> mAssignedWorker;
	void assignWorker(std::shared_ptr<Worker> worker);
private:
	

	bool mIsFinished;
};

