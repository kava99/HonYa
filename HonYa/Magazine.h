#pragma once

#include "Common.hpp"
#include "ObjectContainer.h"
#include "IGuiDebug.h"
#include "Item.h"
#include "Book.h"
#include "GraphicsEngine.h"
#include "IDrawable.h"

class Magazine : public IGuiDebug, public IDrawable
{
public:
	Magazine();
	~Magazine();

	void renderGuiDebug();

	void draw();

	void buildObject(ObjectType ot, vec2 posInTiles);

	void createItem(ItemType it, uint32_t objectId);
	std::unique_ptr<Item> withdrawItemFromObject(uint32_t idOfItem, uint32_t objectId);
	void putItemIntoObject(std::unique_ptr<Item> item, uint32_t objectId);

	//uint32_t getNumOfBooksReadyToSell() { return mBooksReadyToSell.size(); }
	std::vector<uint32_t> mBooksReadyToSell;

	std::map<uint32_t, uint32_t> mItemBelongings; // first is id of item and secund id of object it belongs to
	std::shared_ptr<Object> getObject(uint32_t id) { return mObjectContainer->getObject(id); }
	std::shared_ptr<Object> getObjectByItem(uint32_t id);

private:
	int mMapWidthTiles;
	int mMapHeightTiles;

	std::vector<int> mObjectMap;
	std::unique_ptr<ObjectContainer> mObjectContainer;



	ALLEGRO_BITMAP* bfree;
	ALLEGRO_BITMAP* btaken;
	ALLEGRO_FONT* font;
};

