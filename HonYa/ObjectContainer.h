#pragma once

#include "Common.hpp"
#include "IGuiDebug.h"

#include "Object.h"
#include "Shelf.h"
#include "Delivery.h"



class ObjectContainer :	public IGuiDebug
{
public:
	ObjectContainer();
	~ObjectContainer();

	void renderGuiDebug();

	uint32_t createShelf();
	uint32_t createDelivery();
	uint32_t createObject(ObjectType ot);

	bool removeObject(uint32_t id);


	std::shared_ptr<Object> getObject(uint32_t id);
	template <typename T> 
	std::shared_ptr<T>getObjectAs(uint32_t id);


private:
	std::vector<std::shared_ptr<Shelf>> mShelves;
	std::vector<std::shared_ptr<Delivery>> mDeliveries;

	std::vector<std::pair<ObjectType, uint32_t>> mAllObjects;

};

template<typename T>
inline std::shared_ptr<T> ObjectContainer::getObjectAs(uint32_t id)
{
	auto obj = getObject(id);
	if (obj == nullptr)
		return nullptr;
	return std::static_pointer_cast<T>(obj);
}
