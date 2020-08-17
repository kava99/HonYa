#include "common.h"

#include "allegro_wrapper.h"
#include "d3d.h"

d3d_mesh test_mesh;
d3d_buffer buffer;

void on_init() {
	allegro_wrapper_window_create({800, 600}, "HonYa");
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

	test_mesh.data = test_verts;
	test_mesh.num_of_verts = 8;

	buffer = d3d_buffer_create(test_mesh);

}

void on_exit() {
	d3d_buffer_destroy(buffer);

	allegro_wrapper_window_destroy();
}

void on_update(float tick) {

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