#pragma once

#include "Common.hpp"
#include "IGuiDebug.h"
#include "Item.h"

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





	uint32_t putItem(std::unique_ptr<Item> item); // It will return pos in mItems array; if cannot put item it will retunr -1
	std::unique_ptr<Item> withdrawItem(uint32_t id);

protected:
	std::vector<std::unique_ptr<Item>> mItems;

	void setDefaultValues();
	void initItemList();
};

