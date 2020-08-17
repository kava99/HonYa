#include "allegro_wrapper.h"


ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
ALLEGRO_DISPLAY* display = nullptr;
vec2 window_dim = {32, 32};
bool ready_to_render = false;

void allegro_wrapper_window_create(vec2 dim, std::string title)
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

	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		std::cout << "Cannot init event queue\n";
		return;
	}

	if (!al_install_keyboard())
	{
		std::cout << "Cannot init keyboard\n";
		return;
	}
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	if (!al_install_mouse())
	{
		std::cout << "Cannot init mouse\n";
		return;
	}
	al_register_event_source(event_queue, al_get_mouse_event_source());

	if (!al_init_primitives_addon())
	{
		std::cout << "Cannot init primitives addon\n";
		return;
	}


	if (display != nullptr) return;
	if (!al_is_system_installed()) return;

	al_set_new_display_flags(ALLEGRO_DIRECT3D);

	display = al_create_display(dim.x, dim.y);
	if (!display) {
		std::cout << "Cannot init window\n";
		return;
	}
	window_dim = dim;
	al_set_window_title(display, title.c_str());

	al_register_event_source(event_queue, al_get_display_event_source(display));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplAllegro5_Init(display);

	ready_to_render = true;
}

void allegro_wrapper_window_destroy()
{
	if (display == nullptr) return;
	ImGui_ImplAllegro5_Shutdown();
	ImGui::DestroyContext();

	al_destroy_display(display);
	display = nullptr;
	al_destroy_event_queue(event_queue);
	event_queue = nullptr;
	ready_to_render = false;

	al_uninstall_system();
}

LPDIRECT3DDEVICE9 allegro_wrapper_get_d3d_device()
{
	if (display != nullptr) {
		return al_get_d3d_device(display);
	}
	return nullptr;
}

bool allegro_wrapper_frame_begin()
{
	if (!ready_to_render) return false;

	while (!al_is_event_queue_empty(event_queue)) {
		ALLEGRO_EVENT event;

		al_get_next_event(event_queue, &event);

		ImGui_ImplAllegro5_ProcessEvent(&event);

		switch (event.type)
		{
			if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
			{
				ImGui_ImplAllegro5_InvalidateDeviceObjects();
				al_acknowledge_resize(display);
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

void allegro_wrapper_frame_end()
{
	ImGui::Render();
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
	al_flip_display();
}
