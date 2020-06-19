#include "WorkersUnion.h"


WorkersUnion::WorkersUnion()
{
}

WorkersUnion::~WorkersUnion()
{
}

void WorkersUnion::renderGuiDebug()
{
	if (ImGui::TreeNode("Idle")) {

		for (auto& worker : mIdleWorkers) {
			ImGui::Text("Worker: %s", taskTypeString[worker->mTaskType].c_str());
		}

		ImGui::TreePop();
	}


	if (ImGui::TreeNode("Working")) {

		for (auto& worker : mWorkingWorkers) {
			ImGui::Text("Worker: %s", taskTypeString[worker->mTaskType].c_str());
		}

		ImGui::TreePop();
	}

}

void WorkersUnion::draw()
{
	for (auto& worker : mIdleWorkers) {
		worker->draw();
	}

	for (auto& worker : mWorkingWorkers) {
		worker->draw();
	}

}

void WorkersUnion::update(float ticks)
{
	for (auto& worker : mIdleWorkers) {
		worker->update(ticks);
	}

	for (auto& worker : mWorkingWorkers) {
		worker->update(ticks);
	}
}

void WorkersUnion::createNewWorker()
{
	std::shared_ptr<Worker> w = std::make_shared<Worker>();
	mIdleWorkers.push_back(w);
}

std::shared_ptr<Worker> WorkersUnion::getIdleWorker()
{
	std::shared_ptr<Worker> w;
	if (mIdleWorkers.size() >= 0)
		w = mIdleWorkers.back();
	else
		return nullptr;
	
	mIdleWorkers.pop_back();

	mWorkingWorkers.push_back(w);

	return w;
}

void WorkersUnion::returnWorker(std::shared_ptr<Worker> worker)
{
	mWorkingWorkers.erase(std::remove(mWorkingWorkers.begin(), mWorkingWorkers.end(), worker), mWorkingWorkers.end());
	worker->mTaskType = TaskType::IDLE;
	mIdleWorkers.push_back(worker);

}
