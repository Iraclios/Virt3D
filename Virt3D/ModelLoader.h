#pragma once
#include <string>
#include <fstream>
#include "Model3D.h"
class ModelLoader
{
public:
	bool isLoad(const wchar_t* path);
	static Model3D Load(const wchar_t* path) {
		std::vector<Vector3D> vertices;
		std::vector<int> indices;
		std::ifstream in;
		in.open(path);
		std::string s;
		while (!in.eof()) {
			getline(in, s, '\n');
			if (s[0] == 'v') {
				int x_start = s.find_first_of("-1234567890.");
				int x_end = s.find_first_of(" ", x_start);
				int y_start = s.find_first_of("-1234567890.", x_end);
				int y_end = s.find_first_of(" ", y_start);
				int z_start = s.find_first_of("-1234567890.", y_end);
				int z_end = s.find_first_of(" \n", z_start);
				double x = std::stod(s.substr(x_start, x_end - x_start));
				double y = std::stod(s.substr(y_start, y_end - y_start));
				double z = std::stod(s.substr(z_start, z_end - z_start));
				vertices.push_back(Vector3D(x, y, z));
			}
			else if (s[0] == 'f') {
				int x_start = s.find_first_of("1234567890");
				int x_end = s.find_first_of(" ", x_start);
				int y_start = s.find_first_of("1234567890", x_end);
				int y_end = s.find_first_of(" ", y_start);
				int z_start = s.find_first_of("1234567890", y_end);
				int z_end = s.find_first_of(" \n", z_start);
				double x = std::stoi(s.substr(x_start, x_end - x_start));
				double y = std::stoi(s.substr(y_start, y_end - y_start));
				double z = std::stoi(s.substr(z_start, z_end - z_start));
				indices.push_back(x);
				indices.push_back(y);
				indices.push_back(z);
			}
		}
		in.close();
		return Model3D(vertices, indices);
	}
};

