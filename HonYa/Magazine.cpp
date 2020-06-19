#include "Magazine.h"

Magazine::Magazine()
{
	mMapWidthTiles = 24;
	mMapHeightTiles = 24;
	mObjectMap.resize(mMapWidthTiles * mMapHeightTiles);
	std::fill(mObjectMap.begin(), mObjectMap.end(), -1);
	mObjectContainer = std::make_unique<ObjectContainer>();
	mItemBelongings = std::map<uint32_t, uint32_t>();


	bfree = al_load_bitmap("free.png");
	btaken = al_load_bitmap("taken.png");
	font = al_create_builtin_font();
}

Magazine::~Magazine()
{
}

void Magazine::renderGuiDebug()
{
	mObjectContainer->renderGuiDebug();
	if (ImGui::TreeNode("Item Belongings")) {

		for (auto& it : mItemBelongings) {
			ImGui::Text("Item: '%i' belongs to '%i' object", it.first, it.second);
		}

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Books ready to sell")) {

		for (auto& it : mBooksReadyToSell) {
			ImGui::Text("Book: '%i'", it);
		}

		ImGui::TreePop();
	}
}

void Magazine::draw()
{
	std::vector<int> map  = mObjectMap;
	int width = mMapWidthTiles;
	int height = mMapHeightTiles;


	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (map[(y * width) + x] == -1)
				al_draw_bitmap(bfree, x * 32, y * 32, 0);
			else {
				al_draw_bitmap(btaken, x * 32, y * 32, 0);
				std::string note = std::to_string(map[(y * width) + x]);
				al_draw_text(font, al_map_rgb(255, 255, 255), (x * 32) + 1, (y * 32) + 12, 0, note.c_str());
			}
		}
	}
}

void Magazine::buildObject(ObjectType ot, vec2 posInTiles)
{
	//TODO: Check if position is availble in mObjectMap
	if (ot == ObjectType::NONE) return;
	uint32_t objId = mObjectContainer->createObject(ot);
	auto obj = mObjectContainer->getObject(objId);



	for (int y = 0; y < obj->mSizeInTiles.y; ++y) {
		for (int x = 0; x < obj->mSizeInTiles.x; ++x) {

			int posInTiles1D = ((posInTiles.y + y) * mMapWidthTiles) + (posInTiles.x + x);
			if (posInTiles1D >= mObjectMap.size() || posInTiles1D < 0
				|| (posInTiles.y + y) >= mMapHeightTiles
				|| (posInTiles.x + x) >= mMapWidthTiles) {
				std::cout << "Cannot place object! Not inbound of map!\n"; //TODO: remove object
				return;
			}
			
			mObjectMap[posInTiles1D] = objId;
		}
	}



	vec4 posObj = {
		(posInTiles.x * TILE_SIZE),
		(posInTiles.y * TILE_SIZE),
		(posInTiles.x * TILE_SIZE) + (obj->mSizeInTiles.x * TILE_SIZE),
		(posInTiles.y * TILE_SIZE) + (obj->mSizeInTiles.y * TILE_SIZE),
	};
	obj->mPosition = posObj;


	std::string name = obj->mInGameName;
	name.append(std::to_string(obj->mUniqueId));
	obj->mInGameName = name;
}

void Magazine::createItem(ItemType it, uint32_t objectId)
{
	std::unique_ptr<Item> item;
	switch (it) {
		case ItemType::BOOK:
			item = std::make_unique<Book>();
			break;
	}
	putItemIntoObject(std::move(item), objectId);

}

std::unique_ptr<Item> Magazine::withdrawItemFromObject(uint32_t idOfItem, uint32_t objectId)
{
	auto obj = mObjectContainer->getObject(objectId);
	if (obj == nullptr) return nullptr;
	auto item = obj->withdrawItem(idOfItem);
	if (item != nullptr) {
		mItemBelongings.erase(idOfItem);
		if (item->mItemType == ItemType::BOOK && obj->mObjectType == ObjectType::SHELF)
			mBooksReadyToSell.erase(std::remove(mBooksReadyToSell.begin(), mBooksReadyToSell.end(), idOfItem), mBooksReadyToSell.end());
	}
		

	return std::move(item);
}

void Magazine::putItemIntoObject(std::unique_ptr<Item> item, uint32_t objectId)
{
	uint32_t itemId = item->mUniqueId;
	auto itemType = item->mItemType;

	auto obj = mObjectContainer->getObject(objectId);
	if (obj == nullptr) {
		std::cout << "Cannot put into: " << objectId << " object. Object doesn't exist!\n";
		return;
	}

	if (obj->putItem(std::move(item)) == -1) {
		std::cout << "Cannot put into: " << objectId << " object. Object has no space!\n";
		return;
	}

	mItemBelongings[itemId] = objectId;
	if(itemType == ItemType::BOOK && obj->mObjectType == ObjectType::SHELF)
		mBooksReadyToSell.push_back(itemId);
}

std::shared_ptr<Object> Magazine::getObjectByItem(uint32_t id)
{
	if (mItemBelongings.count(id) == 0) return nullptr;
	return getObject(mItemBelongings[id]);
}
