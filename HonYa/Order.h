#pragma once

#include "Common.hpp"
#include "IGuiDebug.h"


static uint32_t nextOrderId = 0;
static inline uint32_t getNextOrderId() {
	return nextOrderId++;
}

class Order : public IGuiDebug
{
public:
	Order();
	~Order();

	void renderGuiDebug();
	
	uint32_t mUniqueId;
	std::vector<uint32_t> mBookIds;


};

