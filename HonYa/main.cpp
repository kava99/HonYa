
#include "Common.hpp"
#include "GraphicsEngine.h"
#include "DebugGui.h"
#include "Magazine.h"
#include "WorkersUnion.h"
#include "OrderManager.h"


#include "ObjectContainer.h"

std::unique_ptr<GraphicsEngine> gGraphicsEngine;
std::unique_ptr<Magazine> gMagazine;
std::unique_ptr<WorkersUnion> gWorkersUnion;
std::unique_ptr<OrderManager> gOrderManager;

void onInitialization() {
	gGraphicsEngine = std::make_unique<GraphicsEngine>();
	gGraphicsEngine->createWindow({1366, 768});


	gMagazine = std::make_unique<Magazine>();
	gMagazine->buildObject(ObjectType::SHELF, vec2(3, 3));
	gMagazine->buildObject(ObjectType::SHELF, vec2(3, 5));
	gMagazine->buildObject(ObjectType::DELIVERY, vec2(9, 9));
	gMagazine->createItem(ItemType::BOOK, 0);
	gMagazine->createItem(ItemType::BOOK, 0);
	gMagazine->createItem(ItemType::BOOK, 0);
	gMagazine->createItem(ItemType::BOOK, 0);
	gMagazine->createItem(ItemType::BOOK, 0);
	gMagazine->createItem(ItemType::BOOK, 1);
	gMagazine->createItem(ItemType::BOOK, 2);

	gMagazine->withdrawItemFromObject(2, 0);


	gWorkersUnion = std::make_unique<WorkersUnion>();
	gWorkersUnion->createNewWorker();
	gWorkersUnion->createNewWorker();

	gOrderManager = std::make_unique<OrderManager>();
}

void update(float ticks) {
	gOrderManager->update(ticks);
	gMagazine->mBooksReadyToSell = gOrderManager->acceptPendingOrder(gMagazine->mBooksReadyToSell);
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


	std::chrono::duration<float> diff;
	while(true){
		
		auto start = std::chrono::high_resolution_clock::now();
		update(diff.count());
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
