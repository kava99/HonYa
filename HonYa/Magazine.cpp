#include "Magazine.h"

Magazine::Magazine()
{
	mMapWidthTiles = 24;
	mMapHeightTiles = 24;
	mObjectMap.resize(mMapWidthTiles * mMapHeightTiles);
	std::fill(mObjectMap.begin(), mObjectMap.end(), -1);
	mObjectContainer = std::make_unique<ObjectContainer>();


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
}

void Magazine::drawMap()
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
