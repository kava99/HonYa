#pragma once

#include "Common.hpp"
#include "ObjectContainer.h"
#include "IGuiDebug.h"
#include "Item.h"
#include "Book.h"
#include "GraphicsEngine.h"

class Magazine : public IGuiDebug
{
public:
	Magazine();
	~Magazine();

	void renderGuiDebug();

	void drawMap();

	void buildObject(ObjectType ot, vec2 posInTiles);

	void createItem(ItemType it, uint32_t objectId);
	std::unique_ptr<Item> withdrawItemFromObject(uint32_t idOfItem, uint32_t objectId);
	void putItemIntoObject(std::unique_ptr<Item> item, uint32_t obejctId);

private:
	int mMapWidthTiles;
	int mMapHeightTiles;

	std::vector<int> mObjectMap;
	std::unique_ptr<ObjectContainer> mObjectContainer;
	std::map<uint32_t, uint32_t> mItemBelongings; // first is id of book and secund id of object it belongs to

	ALLEGRO_BITMAP* bfree;
	ALLEGRO_BITMAP* btaken;
	ALLEGRO_FONT* font;
};

