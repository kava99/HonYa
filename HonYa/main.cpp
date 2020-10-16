#include "common.h"

#include "allegro_wrapper.h"
#include "d3d.h"

d3d_mesh test_mesh;
d3d_buffer buffer;

void on_init() {
	allegro_wrapper_window_create({1366, 768}, "HonYa");
	d3d_init(allegro_wrapper_get_d3d_device());

	d3d_buffer_vertex_struct test_verts[] =
	{
		{ -3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ 3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ -3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 0, 0), },
		{ 3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 255), },
		{ -3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ 3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(255, 0, 0), },
		{ -3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ 3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 255), },
	};

	test_mesh.v_data = test_verts;
	test_mesh.num_of_verts = 8;

	UINT32 indices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};

	loader::mesh loaded_mesh = loader::load_obj_from_file_to_mesh("untitled.obj");

	test_mesh.i_data = indices;
	test_mesh.num_of_indices = 36;

	buffer = d3d_buffer_create(loaded_mesh);

}

void on_exit() {
	d3d_buffer_destroy(buffer);

	allegro_wrapper_window_destroy();
}

void on_update(float tick) {
	
	if (ImGui::GetIO().KeysDown[ALLEGRO_KEY_D])
		camera_move_right(1.0f);	
	if (ImGui::GetIO().KeysDown[ALLEGRO_KEY_A])
		camera_move_right(-1.0f);
	if (ImGui::GetIO().KeysDown[ALLEGRO_KEY_W])
		camera_move_up(1.0f);	
	if (ImGui::GetIO().KeysDown[ALLEGRO_KEY_S])
		camera_move_up(-1.0f);
	if (ImGui::GetIO().KeysDown[ALLEGRO_KEY_R])
		camera_zoom(1.0f);	
	if (ImGui::GetIO().KeysDown[ALLEGRO_KEY_F])
		camera_zoom(-1.0f);
}

void on_render() {
	if (allegro_wrapper_frame_begin()) {

		d3d_buffer_render(buffer);

		allegro_wrapper_frame_end();
	}
}


int main(int argc, char** argv) {

	on_init();


	int fps = 180;
	float secs_per_frame = 1.0f / fps;


	std::chrono::duration<float> diff = std::chrono::duration<float>::zero();
	while (true) {

		auto start = std::chrono::high_resolution_clock::now();
		on_update(static_cast<float>(diff.count()));
		on_render();
		auto end = std::chrono::high_resolution_clock::now();
		diff = end - start;
		while (static_cast<float>(diff.count()) <= secs_per_frame) {
			end = std::chrono::high_resolution_clock::now();
			diff = end - start;
		}
	}

	on_exit();

	return 0;
}