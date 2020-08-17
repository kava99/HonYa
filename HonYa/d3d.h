#pragma once

#include "common.h"

struct d3d_mesh;
struct d3d_buffer_vertex_struct;
struct d3d_buffer;





extern void d3d_init(LPDIRECT3DDEVICE9 dev);






struct d3d_buffer_vertex_struct {
	float x, y, z;
	DWORD color;
};

#define d3d_buffer_vertex_fvf (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct d3d_buffer {
	UINT32 num_of_triangles;
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer;
};

extern d3d_buffer d3d_buffer_create(d3d_mesh mesh);
extern void d3d_buffer_render(d3d_buffer buffer);
extern void d3d_buffer_destroy(d3d_buffer buffer);







struct d3d_mesh {
	d3d_buffer_vertex_struct* data;
	size_t num_of_verts;
};


