#include "Item.h"

Item::Item()
{
	setDefaultValues();
}

Item::~Item()
{

}

void Item::setDefaultValues()
{
	mItemType = ItemType::BLANK;
	mCanHoldInHand = false;
	mInGameName = "Blank";
	mUniqueId = getNextItemId();

}

void Item::appendIdToName()
{
	mInGameName.append(" ");
	mInGameName.append(std::to_string(mUniqueId));
}

