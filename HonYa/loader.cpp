#include "loader.h"

loader::mesh loader::load_obj_from_file_to_mesh(std::string path)
{
    std::ifstream infile(path);
    if (!infile.is_open()) {
        printf("Cannot load obj file: '%s'! File doesn't exist!\n", path.c_str());
        return loader::mesh();
    }

    loader::mesh loaded_mesh = loader::mesh();
    std::vector<loader::vertex> verts;
    std::vector<loader::tex_coord> coords;
    std::vector<loader::normal> normals;
    std::vector<loader::face> faces;
    std::string line;


    while (std::getline(infile, line)){
        printf("%s\n", line.c_str());

        if (line.data()[0] == 'v' && line.data()[1] == ' ') {
            auto tmp = split(line, ' ');
            if (tmp.size() != 4) {
                printf("Cannot load obj file: '%s'! Error while reading vertices, more then 3 vertices per face!\n", path.c_str());
                return loader::mesh();
            }
            loader::vertex vert = {std::stof(tmp[1]), std::stof(tmp[2]), std::stof(tmp[3])};
            verts.push_back(vert);
            std::cout << vert.x << vert.y << vert.z << std::endl;
        }

        if (line.data()[0] == 'v' && line.data()[1] == 't') {
            auto tmp = split(line, ' ');
            if (tmp.size() != 3) {
                printf("Cannot load obj file: '%s'! Error while reading texture coords, more then 2 texture coords per face!\n", path.c_str());
                return loader::mesh();
            }
            loader::tex_coord coord = { std::stof(tmp[1]), std::stof(tmp[2]) };
            coords.push_back(coord);
            std::cout << coord.u << coord.v << std::endl;
        }

        if (line.data()[0] == 'v' && line.data()[1] == 'n') {
            auto tmp = split(line, ' ');
            if (tmp.size() != 4) {
                printf("Cannot load obj file: '%s'! Error while reading normals, more then 3 normals per face!\n", path.c_str());
                return loader::mesh();
            }
            loader::normal normal = { std::stof(tmp[1]), std::stof(tmp[2]), std::stof(tmp[3]) };
            normals.push_back(normal);
            std::cout << normal.x << normal.y << normal.z << std::endl;
        }



        if (line.data()[0] == 'f' && line.data()[1] == ' ') {
            auto tmp = split(line, ' ');
            if (tmp.size() != 4) {
                printf("Cannot load obj file: '%s'! Error while reading faces!\n", path.c_str());
                return loader::mesh();
            }
            loader::face face;
            for (int i = 0; i < 3; ++i) {
                auto f = split(tmp[i + 1], '/');
                face.verts[i] = verts[(std::stoi(f[0]) - 1)];
                face.tex_coords[i] = coords[(std::stoi(f[1]) - 1)];
                face.normals[i] = normals[(std::stoi(f[2]) - 1)];
            }
            faces.push_back(face);
        }
        loaded_mesh.faces = faces;

    }


	return loaded_mesh;
}
