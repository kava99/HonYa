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

inline std::vector<std::string> split(const std::string& text, char sep) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}



#endif // COMMON_HPP