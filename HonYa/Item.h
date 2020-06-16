#pragma once

#include "Common.hpp"

static uint32_t nextItemId = 0;
static inline uint32_t getNextItemId() {
	return nextItemId++;
}


enum class ItemType : int {
	BLANK,
	BOOK,
};

static std::map <ItemType, std::string> itemTypeString = {
	{ ItemType::BLANK, "BLANK" },
	{ ItemType::BOOK, "BOOK" },
};




class Item
{
public:
	Item();
	~Item();

	ItemType mItemType;
	bool mCanHoldInHand;
	std::string mInGameName;
	uint32_t mUniqueId;

protected:
	void setDefaultValues();
	void appendIdToName();


};

