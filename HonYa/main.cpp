
#include "Common.hpp"
#include "GraphicsEngine.h"
#include "DebugGui.h"


#include "ObjectContainer.h"

std::unique_ptr<GraphicsEngine> gGraphicsEngine;
std::unique_ptr<ObjectContainer> gObjectCon;

void onInitialization() {
	gGraphicsEngine = std::make_unique<GraphicsEngine>();
	gGraphicsEngine->createWindow({800, 600});


	gObjectCon = std::make_unique<ObjectContainer>();
	gObjectCon->createShelf();
	gObjectCon->createShelf();
	gObjectCon->createDelivery();
}

void update(float ticks) {

}

void render() {
	if (gGraphicsEngine->beginFrame()) {

		debug_gui::renderBasic();


		ImGui::Begin("Object Container");

		gObjectCon->renderGuiDebug();

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
