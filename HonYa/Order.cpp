#include "Order.h"

Order::Order()
{
	mUniqueId = getNextOrderId();
	mIsCompleted = false;
}

Order::~Order()
{
}

void Order::renderGuiDebug()
{

	if (ImGui::TreeNode(format("Order id: %i", mUniqueId).c_str())) {
		for (auto& book : mBookIds) {
			ImGui::Text("Book id: %i", book);
		}
		ImGui::TreePop();
	}
}
