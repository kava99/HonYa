
#include "Common.hpp"


void onInitialization() {

}

void update(float ticks) {
	std::cout << "Ticks: " << ticks << "\n";

}

void render() {

}

int main(int argc, char **argv){
	
	onInitialization();


	int fps = 120;
	float secsPerFrame = 1.0f / fps;


	std::chrono::duration<float> diff;
	while(true){
		
		auto start = std::chrono::high_resolution_clock::now();
		update(diff.count());
		auto end = std::chrono::high_resolution_clock::now();
		diff = end-start;
		while(static_cast<float>(diff.count()) <= secsPerFrame){
			end = std::chrono::high_resolution_clock::now();
			diff = end-start;
		}
	}
	return 0;
}
