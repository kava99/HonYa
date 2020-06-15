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
#include "external/imgui/imgui.h"
#include <memory>
#include <list>
#include <algorithm>
#include <ctime>
#include <map>


typedef ImVec2 vec2;
typedef ImVec4 vec4;


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