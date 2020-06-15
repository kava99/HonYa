
#include "Common.hpp"
#include "GraphicsEngine.h"

std::unique_ptr<GraphicsEngine> gGraphicsEngine;


void onInitialization() {
	gGraphicsEngine = std::make_unique<GraphicsEngine>();
	gGraphicsEngine->createWindow({800, 600});

}

void update(float ticks) {
	std::cout << "Ticks: " << ticks << "\n";

}

void render() {
	if (gGraphicsEngine->beginFrame()) {


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
