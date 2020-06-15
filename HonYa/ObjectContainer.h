#pragma once

#include "Common.hpp"
#include "IGuiDebug.h"

#include "Object.h"
#include "Shelf.h"



class ObjectContainer :	public IGuiDebug
{
public:
	ObjectContainer();
	~ObjectContainer();

	void renderGuiDebug();

private:
	std::vector<std::unique_ptr<Shelf>> mShelves;

};

