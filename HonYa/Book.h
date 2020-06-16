#pragma once
#include "Item.h" 

class Book : public Item
{
public:
	Book();
	~Book();

	void setName(std::string name) { mInGameName = name; }

};
