#include "Shelf.h"

Shelf::Shelf()
{
	mObjectType = ObjectType::SHELF;
	mInGameName = "Shelf";
	mSizeInTiles = { 3,1 };
	mCapacity = 50;
	mSpaceTaken = 0;


	//initItemList();

}

Shelf::~Shelf()
{
}


