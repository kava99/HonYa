#ifndef COMMON_HPP
#define COMMON_HPP


#include <stdio.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <memory>
#include <list>
#include <algorithm>
#include <ctime>
#include <map>


#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_allegro5.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_direct3d.h>


#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")


#define TILE_SIZE 32

typedef ImVec2 vec2;
typedef ImVec4 vec4;


struct vec2i {
	vec2i(int x, int y) { this->x = x; this->y = y; }
	vec2i() { this->x = 0; this->y = 0; }
	int x;
	int y;
};


inline std::string format(const char* fmt, ...) {
	int size = 512;
	char* buffer = 0;
	buffer = new char[size];
	va_list vl;
	va_start(vl, fmt);
	int nsize = vsnprintf(buffer, size, fmt, vl);
	if (size <= nsize) {
		delete[] buffer;
		buffer = 0;
		buffer = new char[nsize + 1];
		nsize = vsnprintf(buffer, size, fmt, vl);
	}
	std::string ret(buffer);
	va_end(vl);
	delete[] buffer;
	return ret;
}



#endif // COMMON_HPP