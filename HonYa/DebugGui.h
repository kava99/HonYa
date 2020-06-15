#pragma once

#include "Common.hpp"

namespace debug_gui {
	void renderBasic() {
		ImGui::Begin("Debug");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Mouse pos: %ix%i", (int)ImGui::GetIO().MousePos.x, (int)ImGui::GetIO().MousePos.y);
		
		ImGui::End();
	}
};