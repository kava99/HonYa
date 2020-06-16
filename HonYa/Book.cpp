#include "Book.h"

Book::Book()
{
	mItemType = ItemType::BOOK;
	mCanHoldInHand = true;
	mInGameName = "Book";
	appendIdToName();
}

Book::~Book()
{
}

