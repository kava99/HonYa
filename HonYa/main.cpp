
#include "Common.hpp"
#include "GraphicsEngine.h"
#include "DebugGui.h"
#include "Magazine.h"


#include "ObjectContainer.h"

std::unique_ptr<GraphicsEngine> gGraphicsEngine;
std::unique_ptr<Magazine> gMagazine;

void onInitialization() {
	gGraphicsEngine = std::make_unique<GraphicsEngine>();
	gGraphicsEngine->createWindow({800, 600});


	gMagazine = std::make_unique<Magazine>();
	gMagazine->buildObject(ObjectType::SHELF, vec2(3, 3));
	gMagazine->buildObject(ObjectType::SHELF, vec2(3, 5));
	gMagazine->buildObject(ObjectType::DELIVERY, vec2(9, 9));
}

void update(float ticks) {

}

void render() {
	if (gGraphicsEngine->beginFrame()) {

		gMagazine->drawMap();



		debug_gui::renderBasic();

		ImGui::Begin("Object Container");

		gMagazine->renderGuiDebug();

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
