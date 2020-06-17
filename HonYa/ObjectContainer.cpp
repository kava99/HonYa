#include "ObjectContainer.h"

ObjectContainer::ObjectContainer()
{
}

ObjectContainer::~ObjectContainer()
{
}

void ObjectContainer::renderGuiDebug()
{
	int counter = 0;

	if (ImGui::TreeNode("Shelves")) {
		
		for (auto& sh : mShelves) {
			if (sh == nullptr) continue;
			ImGui::PushID(counter);
			counter++;
			if (ImGui::TreeNode(sh->mInGameName.c_str())) {
				sh->renderGuiDebug();
				ImGui::TreePop();
			}
			ImGui::PopID();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Deliveries")) {
		for (auto& d : mDeliveries) {
			if (d == nullptr) continue;
			ImGui::PushID(counter);
			counter++;
			if (ImGui::TreeNode(d->mInGameName.c_str())) {
				d->renderGuiDebug();
				ImGui::TreePop();
			}
			ImGui::PopID();
		}
		ImGui::TreePop();
	}
}

uint32_t ObjectContainer::createShelf()
{
	std::shared_ptr<Shelf> sh = std::make_shared<Shelf>();

	uint32_t shId = mShelves.size();

	mShelves.push_back(sh);

	uint32_t id = mAllObjects.size();
	sh->mUniqueId = id;
	mAllObjects.push_back(std::make_pair(sh->mObjectType, shId));

	return id;
}

uint32_t ObjectContainer::createDelivery()
{
	std::shared_ptr<Delivery> d = std::make_shared<Delivery>();

	uint32_t dId = mDeliveries.size();

	mDeliveries.push_back(d);

	uint32_t id = mAllObjects.size();
	d->mUniqueId = id;
	mAllObjects.push_back(std::make_pair(d->mObjectType, dId));

	return id;
}

uint32_t ObjectContainer::createObject(ObjectType ot)
{
	switch (ot) {
	case ObjectType::SHELF:
		return createShelf();
		break;
	case ObjectType::DELIVERY:
		return createDelivery();
		break;
	}
	return 0;
}

bool ObjectContainer::removeObject(uint32_t id)
{
	auto p = mAllObjects[id];
	
	switch (p.first) {
		case ObjectType::SHELF:
			mShelves[p.second] = nullptr;
			break;
		case ObjectType::DELIVERY:
			mDeliveries[p.second] = nullptr;
			break;
	}

	return true;
}

std::shared_ptr<Object> ObjectContainer::getObject(uint32_t id)
{
	if (id >= mAllObjects.size()) return nullptr;

	auto p = mAllObjects[id];


	switch (p.first) {
	case ObjectType::SHELF:
		return std::static_pointer_cast<Object>(mShelves[p.second]);
		break;
	case ObjectType::DELIVERY:
		return std::static_pointer_cast<Object>(mDeliveries[p.second]);
		break;
	}
	return std::shared_ptr<Object>();
}
