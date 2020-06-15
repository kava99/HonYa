#pragma once

#include "Common.hpp"
#include "external/imgui/imgui_impl_allegro5.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	void createWindow(vec2 dim);
	void closeWindow();


	bool beginFrame();
	void endFrame();
	bool canRender() { return mReadyToRender; }

private:
	ALLEGRO_EVENT_QUEUE* mQueue;

	ALLEGRO_DISPLAY* mAllDisplay;
	bool mReadyToRender;

	vec2 mDimesnions;
};

