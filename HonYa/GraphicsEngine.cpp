#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
{
	mAllDisplay = nullptr;
	mQueue = nullptr;
	mReadyToRender = false;
	mDimesnions = { 32, 32 };
}

GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::createWindow(vec2 dim)
{
	if (al_is_system_installed()) return;
	if (!al_init()) {
		std::cout << "Cannot init allegro\n";
		return;
	}

	if (!al_init_image_addon())
	{
		std::cout << "Cannot init allegro init addon\n";
		return;
	}

	mQueue = al_create_event_queue();
	if (!mQueue)
	{
		std::cout << "Cannot init event queue\n";
		return;
	}

	if (!al_install_keyboard())
	{
		std::cout << "Cannot init keyboard\n";
		return;
	}
	al_register_event_source(mQueue, al_get_keyboard_event_source());


	if (!al_install_mouse())
	{
		std::cout << "Cannot init mouse\n";
		return;
	}
	al_register_event_source(mQueue, al_get_mouse_event_source());

	if (!al_init_primitives_addon())
	{
		std::cout << "Cannot init primitives addon\n";
		return;
	}


	if (mAllDisplay != nullptr) return;
	if (!al_is_system_installed()) return;
	mAllDisplay = al_create_display(dim.x, dim.y);
	if (!mAllDisplay) {
		std::cout << "Cannot init window\n";
		return;
	}
	mDimesnions = dim;

	al_register_event_source(mQueue, al_get_display_event_source(mAllDisplay));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplAllegro5_Init(mAllDisplay);

	mReadyToRender = true;
}

void GraphicsEngine::closeWindow()
{
	if (mAllDisplay == nullptr) return;
	ImGui_ImplAllegro5_Shutdown();
	ImGui::DestroyContext();

	al_destroy_display(mAllDisplay);
	mAllDisplay = nullptr;
	al_destroy_event_queue(mQueue);
	mQueue = nullptr;
	mReadyToRender = false;

	al_uninstall_system();
}

bool GraphicsEngine::beginFrame()
{
	if (!mReadyToRender) return false;

	while (!al_is_event_queue_empty(mQueue)) {
		ALLEGRO_EVENT event;

		al_get_next_event(mQueue, &event);

		ImGui_ImplAllegro5_ProcessEvent(&event);

		switch (event.type)
		{
			if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
			{
				ImGui_ImplAllegro5_InvalidateDeviceObjects();
				al_acknowledge_resize(mAllDisplay);
				ImGui_ImplAllegro5_CreateDeviceObjects();
			}
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			exit(0);
		}
	}


	ImGui_ImplAllegro5_NewFrame();
	ImGui::NewFrame();
	al_clear_to_color(al_map_rgb(12, 24, 66));

	return true;
}

void GraphicsEngine::endFrame()
{
	ImGui::Render();
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
	al_flip_display();
}
