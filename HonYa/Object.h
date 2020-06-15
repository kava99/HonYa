#pragma once

#include "Common.hpp"
#include "IGuiDebug.h"

enum class ObjectType : int {
	NONE,
	SHELF,
	DELIVERY,
};


static std::map<ObjectType, std::string> objectTypeString{
		{ ObjectType::NONE, "NONE" },
		{ ObjectType::SHELF, "SHELF" },
		{ ObjectType::DELIVERY, "DELIVERY" }
};


class Object : public IGuiDebug
{
public:


	Object();
	~Object();

	ObjectType mObjectType;
	std::string mInGameName;
	vec2 mSizeInTiles;
	uint32_t mUniqueId;
	vec4 mPosition;
	int mCapacity;
	int mSpaceTaken;

	void renderGuiDebug();



	/*std::vector<std::shared_ptr<Item>> mItems;

	int putItem(std::shared_ptr<Item> item); // It will return pos in mItems array; if cannot put item it will retunr -1
	std::shared_ptr<Item> withdrawItem(int id);
	int withdrawItem(std::shared_ptr<Item> item);*/

protected:
	void setDefaultValues();
	void initItemList();
};

