#pragma once

#include "Common.hpp"
#include "ObjectContainer.h"
#include "IGuiDebug.h"
#include "GraphicsEngine.h"

class Magazine : public IGuiDebug
{
public:
	Magazine();
	~Magazine();

	void renderGuiDebug();

	void drawMap();

	void buildObject(ObjectType ot, vec2 posInTiles);

private:
	int mMapWidthTiles;
	int mMapHeightTiles;

	std::vector<int> mObjectMap;
	std::unique_ptr<ObjectContainer> mObjectContainer;


	ALLEGRO_BITMAP* bfree;
	ALLEGRO_BITMAP* btaken;
	ALLEGRO_FONT* font;
};

