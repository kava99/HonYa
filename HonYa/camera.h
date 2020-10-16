#pragma once

#include "common.h"

extern D3DXMATRIX camera_get_matrix();
extern D3DXVECTOR3 camera_get_position();
extern void camera_move_right(float v);
extern void camera_move_up(float v);
extern void camera_zoom(float v);
