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
	ImGui::Text("Object Type: %s", objectTypeString[mObjectType].c_str());
	ImGui::Text("InGame Name: %s", mInGameName.c_str());
	ImGui::Text("Size in tiles: %ix%i", (int)mSizeInTiles.x, (int)mSizeInTiles.y);
	ImGui::Text("Unique id: %i", mUniqueId);
	ImGui::Text("Position: %i, %i, %i, %i", (int)mPosition.x, (int)mPosition.y, (int)mPosition.z, (int)mPosition.w);
	ImGui::Text("Space taken: %i", mSpaceTaken);
	if (mCapacity != -1) {
		if (ImGui::TreeNode(format("Capacity: %i", mCapacity).c_str())) {

			/*auto items = obj->mItems;

			for (int i = 0; i < items.size(); ++i) {
				if (items[i] == nullptr)
					ImGui::Text("%i: nullptr", i);
				else
					ImGui::Text("%i: %s", i, items[i]->mInGameName.c_str());
			}*/


			ImGui::TreePop();
		}
	}
	else
		ImGui::Text("Capacity: %i", mCapacity);

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
