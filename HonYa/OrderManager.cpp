#include "OrderManager.h"

OrderManager::OrderManager()
{
	srand(static_cast <unsigned int> (time(0)));
}

OrderManager::~OrderManager()
{
}

void OrderManager::renderGuiDebug()
{
	ImGui::Text("Number of pending orders: %i", mPendingOrders.size());
	for (auto& ords : mOrders) {
		ords->renderGuiDebug();
	}
}

void OrderManager::update(float ticks)
{
	for (auto& ord : mOrders) {
		if (ord->mIsCompleted) {
			mOrders.erase(std::remove(mOrders.begin(), mOrders.end(), ord), mOrders.end());
			break;
		}
	}

	if (mPendingOrders.size() < 6) {
		//mPendingOrders.push_back((rand() % (2)) + 1);
		mPendingOrders.push_back(1);
	}


}

std::vector<uint32_t> OrderManager::acceptPendingOrder(std::vector<uint32_t> booksIds)
{
	std::vector<uint32_t> ret;
	ret = booksIds;
	


	if (mPendingOrders.size() > 0 && ret.size() >= mPendingOrders.back()) {

		std::shared_ptr<Order> ord = std::make_shared<Order>();


		for (int i = 0; i < mPendingOrders.back(); ++i) {
			int chosenBook = rand() % (ret.size());

			ord->mBookIds.push_back(ret[chosenBook]);
			ret.erase(std::remove(ret.begin(), ret.end(), ord->mBookIds.back()), ret.end());
			
		}

		TaskManager::Instance()->pushOrderCompletionTask(ord);
		mPendingOrders.pop_back();
		mOrders.push_back(ord);

	}


	return ret;
}
