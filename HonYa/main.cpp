
#include "Common.hpp"
#include "GraphicsEngine.h"
#include "DebugGui.h"
#include "Magazine.h"
#include "WorkersUnion.h"
#include "OrderManager.h"
#include "TaskManager.h"
#include "Timer.h"

#include "ObjectContainer.h"

std::unique_ptr<GraphicsEngine> gGraphicsEngine;
std::shared_ptr<Magazine> gMagazine;
std::shared_ptr<WorkersUnion> gWorkersUnion;
std::unique_ptr<OrderManager> gOrderManager;

void onInitialization() {
	gGraphicsEngine = std::make_unique<GraphicsEngine>();
	gGraphicsEngine->createWindow({1366, 768});


	gMagazine = std::make_shared<Magazine>();
	gMagazine->buildObject(ObjectType::SHELF, vec2(3, 3));
	gMagazine->buildObject(ObjectType::SHELF, vec2(3, 5));
	gMagazine->buildObject(ObjectType::SHELF, vec2(18, 1));
	gMagazine->buildObject(ObjectType::SHELF, vec2(20, 22));
	gMagazine->buildObject(ObjectType::DELIVERY, vec2(9, 9));

	gMagazine->createItem(ItemType::BOOK, 0);
	gMagazine->createItem(ItemType::BOOK, 1);
	gMagazine->createItem(ItemType::BOOK, 0);
	gMagazine->createItem(ItemType::BOOK, 1);
	gMagazine->createItem(ItemType::BOOK, 0);
	gMagazine->createItem(ItemType::BOOK, 1);
	gMagazine->createItem(ItemType::BOOK, 2);

	gMagazine->withdrawItemFromObject(2, 0);


	gWorkersUnion = std::make_shared<WorkersUnion>();
	gWorkersUnion->createNewWorker();
	gWorkersUnion->createNewWorker();
	gWorkersUnion->createNewWorker();
	gWorkersUnion->createNewWorker();
	gWorkersUnion->createNewWorker();
	gWorkersUnion->createNewWorker();

	gOrderManager = std::make_unique<OrderManager>();

	TaskManager::Instance()->mMagazine = gMagazine;
	TaskManager::Instance()->mWorkersUnion = gWorkersUnion;

}
float x = 0;
void update(float ticks) {

	gWorkersUnion->update(ticks);
	gOrderManager->update(ticks);
	gMagazine->mBooksReadyToSell = gOrderManager->acceptPendingOrder(gMagazine->mBooksReadyToSell);
	TaskManager::Instance()->update(ticks);

	static Timer timer;
	timer.update(ticks);
	if (timer.timePassed() >= 1.0f) {
		timer.reset();
		for (int i = 0; i < 4; ++i) {
			gMagazine->createItem(ItemType::BOOK, i);
		}
	}
}

void render() {
	if (gGraphicsEngine->beginFrame()) {

		gMagazine->draw();
		gWorkersUnion->draw();


		debug_gui::renderBasic();

		ImGui::Begin("Object Container");
		gMagazine->renderGuiDebug();
		ImGui::End();
		ImGui::Begin("Workers");
		gWorkersUnion->renderGuiDebug();
		ImGui::End();
		ImGui::Begin("Order");
		gOrderManager->renderGuiDebug();
		ImGui::End();

		gGraphicsEngine->endFrame();
	}
}

int main(int argc, char **argv){
	
	onInitialization();


	int fps = 480;
	float secsPerFrame = 1.0f / fps;


	std::chrono::duration<float> diff = std::chrono::duration<float>::zero();
	while(true){
		
		auto start = std::chrono::high_resolution_clock::now();
		update(static_cast<float>(diff.count()));
		render();
		auto end = std::chrono::high_resolution_clock::now();
		diff = end-start;
		while(static_cast<float>(diff.count()) <= secsPerFrame){
			end = std::chrono::high_resolution_clock::now();
			diff = end-start;
		}
	}
	return 0;
}
