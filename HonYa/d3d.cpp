#include "d3d.h"

LPDIRECT3DDEVICE9 device = nullptr;


void d3d_init(LPDIRECT3DDEVICE9 dev)
{
	if (dev == nullptr) {
		printf("Cannot d3d_init, direct3ddevice9 is nullptr\n");
		return;
	}

	device = dev;

}

void d3d_buffer_render(d3d_buffer buffer)
{
	if (buffer.vertex_buffer == nullptr)
		return;

	device->SetFVF(d3d_buffer_vertex_fvf);



	D3DXMATRIX matRotateY;
	static float index = 0.0f; index += 0.05f;
	D3DXMatrixRotationY(&matRotateY, index);

	device->SetTransform(D3DTS_WORLD, &matRotateY);

	D3DXMATRIX matView;

	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 0.0f, 10.0f),    // the camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),    // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction

	device->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matProjection;

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(45),    // the horizontal field of view
		(FLOAT)800 / (FLOAT)600, // aspect ratio
		1.0f,    // the near view-plane
		100.0f);    // the far view-plane

	device->SetTransform(D3DTS_PROJECTION, &matProjection);


	device->SetStreamSource(0, buffer.vertex_buffer, 0, sizeof(d3d_buffer_vertex_struct));

	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, buffer.num_of_triangles);
}

void d3d_buffer_destroy(d3d_buffer buffer)
{
	if(buffer.vertex_buffer != nullptr)
		buffer.vertex_buffer->Release();
}

d3d_buffer d3d_buffer_create(d3d_mesh mesh)
{
	d3d_buffer buffer;
	memset(&buffer, 0, sizeof(buffer));
	buffer.num_of_triangles = mesh.num_of_verts / 3;

	device->CreateVertexBuffer(mesh.num_of_verts * sizeof(d3d_buffer_vertex_struct),
		0,
		d3d_buffer_vertex_fvf,
		D3DPOOL_MANAGED,
		&buffer.vertex_buffer,
		NULL);

	VOID* p_void;
	buffer.vertex_buffer->Lock(0, 0, (void**)&p_void, 0);
	memcpy(p_void, mesh.data, mesh.num_of_verts * sizeof(d3d_buffer_vertex_struct));
	buffer.vertex_buffer->Unlock();

	return buffer;
}