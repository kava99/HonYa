#include "camera.h"

D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
D3DXVECTOR3 target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

D3DXMATRIX camera_get_matrix()
{
	D3DXMATRIX mat;
	D3DXMatrixLookAtLH(&mat,
		&position,    // the camera position
		&target,    // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction

	return mat;
}

D3DXVECTOR3 camera_get_position()
{
	return position;
}

void camera_move_right(float v)
{
	position.x -= v;
	target.x -= v;
}

void camera_move_up(float v)
{
	position.y += v;
	target.y += v;
}

void camera_zoom(float v)
{
	position.z -= v;
	target.z -= v;
}
