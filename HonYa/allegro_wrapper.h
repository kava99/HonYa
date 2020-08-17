#pragma once

#include "common.h"

extern void allegro_wrapper_window_create(vec2 dim, std::string title);
extern void allegro_wrapper_window_destroy();

extern LPDIRECT3DDEVICE9 allegro_wrapper_get_d3d_device();

extern bool allegro_wrapper_frame_begin();
extern void allegro_wrapper_frame_end();
