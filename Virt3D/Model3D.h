#pragma once
#include "framework.h"
#include "Vector3D.h"
#include <vector>
#include "AffineTransform.h"
class Model3D
{
	static void line(HDC dc, double x0, double y0, double x, double y) {
		MoveToEx(dc, (int)x0, (int)y0, NULL);
		LineTo(dc, (int)x, (int)y);
	}
	static void triangle(HDC dc, double x1, double y1, double x2, double y2, double x3, double y3) {
		line(dc, x1, y1, x2, y2);
		//line(dc, x1, y1, x3, y3);
		//line(dc, x3, y3, x2, y2);
	}
	std::vector<Vector3D> vertices;
	std::vector<int> indices;
public:
	int verticesNumber() {
		return vertices.size();
	}
	Vector3D vertice(int n) {
		return vertices[n];
	}
	Model3D(const std::vector<Vector3D>& vertices, const std::vector<int>& indices) :
		indices(indices), vertices(vertices) {}
	void applyAT(Matrix affineTransformation) {
		int s = vertices.size();
		for (int i = 0; i < s; i++) {
			Vector3D f = affineTransformation * vertices[i];
			vertices[i]= f;
		}
	}
	Model3D(const Model3D& t) :
		indices(t.indices), vertices(t.vertices) {}
	void draw(Matrix projectionMatrix, HDC dc) {
		int s = vertices.size();
		double* t = new double[4 * s];
		for (int i = 0; i < s; i++) {
			t[i] = vertices[i].getX();
			t[s + i] = vertices[i].getY();
			t[2 * s + i] = vertices[i].getZ();
			t[3 * s + i] = 1;
		}
		Matrix v = projectionMatrix * Matrix(4, s, t);
		delete[] t;
		int n = indices.size();
		for (int i = 0; i < n / 3; i++) {
			double x1 = v.getElement(indices[3 * i]) / v.getElement(indices[3 * i] + 2 * s);
			double y1 = v.getElement(indices[3 * i] + s) / v.getElement(indices[3 * i] + 2 * s);
			double x2 = v.getElement(indices[3 * i + 1]) / v.getElement(indices[3 * i + 1] + 2 * s);
			double y2 = v.getElement(indices[3 * i + 1] + s) / v.getElement(indices[3 * i + 1] + 2 * s);
			double x3 = v.getElement(indices[3 * i + 2]) / v.getElement(indices[3 * i + 2] + 2 * s);
			double y3 = v.getElement(indices[3 * i + 2] + s) / v.getElement(indices[3 * i + 2] + 2 * s);
			triangle(dc, x1, y1, x2, y2, x3, y3);
		}
	}
};

