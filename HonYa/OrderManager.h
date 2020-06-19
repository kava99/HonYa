#pragma once

#include "Common.hpp"
#include "Order.h"
#include "IUpdateble.h"
#include "IGuiDebug.h"
#include "TaskManager.h"


class OrderManager : public IUpdateble, public IGuiDebug
{
public:
	OrderManager();
	~OrderManager();

	void renderGuiDebug();

	void update(float ticks);
	std::vector<uint32_t> acceptPendingOrder(std::vector<uint32_t> booksIds);

	std::vector<uint32_t> mPendingOrders;
	std::vector<std::shared_ptr<Order>> mOrders;
};

