#pragma once

#include "common.h"

namespace loader{
	struct vertex {
		float x, y, z;
	};
	struct tex_coord {
		float u, v;
	};
	struct normal {
		float x, y, z;
	};
	struct face {
		vertex verts[3];
		tex_coord tex_coords[3];
		normal normals[3];
	};
	struct mesh {
		mesh() { }
		std::vector<face> faces;
	};

	mesh load_obj_from_file_to_mesh(std::string path);


}
