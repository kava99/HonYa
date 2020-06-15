#include "Object.h"

Object::Object()
{
	setDefaultValues();
}

Object::~Object()
{
}

void Object::renderGuiDebug()
{
}

void Object::setDefaultValues()
{
	mObjectType = ObjectType::NONE;
	mInGameName = "NONE";
	mSizeInTiles = { 1,1 };
	mUniqueId = 0;
	mPosition = { 0, 0, 0, 0 };
	mCapacity = -1;
	mSpaceTaken = -1;
	//mItems.clear();
}


/*

void Object::initItemList()
{
mItems.resize(mCapacity);
	std::fill(mItems.begin(), mItems.end(), nullptr);
}



int Object::putItem(std::shared_ptr<Item> item)
{
	if (mSpaceTaken == -1 || mCapacity <= 0) return -1;
	if (mSpaceTaken >= mCapacity) return -1;
	if (item == nullptr) return -1;
	//if(item->mItemType == ItemType::BLANK) return -1; // TODO: uncomment this

	mItems[mSpaceTaken] = item;
	mSpaceTaken++;

	item->mIdOfObject = mUniqueId;

	return mSpaceTaken - 1;
}

std::shared_ptr<Item> Object::withdrawItem(int id)
{
}

int Object::withdrawItem(std::shared_ptr<Item> item)
{
}*/
