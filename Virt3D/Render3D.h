#pragma once
#include <vector>
#include "ModelLoader.h"
#include "Model3D.h"
#include "Camera3D.h"
class Render3D
{
private:
	std::vector<Model3D> m_models;
public:
	int width = 0;
	int height = 0;
	void render(HDC dc, int t) {
		if (true) {
			Camera3D c(Vector3D(width / 2, height / 2, 0), Vector3D(0, 0, 1), Vector3D(0, 1, 0));
			Vector3D g = m_models[t - 1].vertice(0);
			m_models[t - 1].draw(c.projectionMatrix(), dc);
		}
	}
	int verticesNumber(int t) {
		if (!t) return 0;
		return m_models[t - 1].verticesNumber();
	}
	Vector3D verticeCoordiante(int t, int n) {
		if (!t) return Vector3D(0, 0, 0);
		return m_models[t - 1].vertice(n);
	}
	void addModel(const Model3D& model) {
		m_models.push_back(model);
	}
	int numberOfModels() {
		return m_models.size();
	}
	void action(HDC dc, int t) {
		MoveToEx(dc, (int)width/2, (int)height/2, NULL);
		LineTo(dc, (int)width/2+20, (int)height/2);
		MoveToEx(dc, (int)width / 2, (int)height / 2, NULL);
		LineTo(dc, (int)width / 2, (int)height / 2 + 20);
		if (t > 0) Render3D::render(dc, t);
	}
	void act(double x, double y, double z, int t, Vector3D p = Vector3D(0, 0, 0), Vector3D q = Vector3D(0, 0, 0), int s = 0) {
		if (s == 3) {
			//this->rotate(x, y, z, t, p, q);
			if (!t) return;
			if (p != q) {
				m_models[t - 1].applyAT(AffineTransform::SelectSide(p, q));
			}
			m_models[t - 1].applyAT(AffineTransform::RotationX(x));
			m_models[t - 1].applyAT(AffineTransform::RotationY(y));
			m_models[t - 1].applyAT(AffineTransform::RotationZ(z));
			if (p != q) {
				m_models[t - 1].applyAT(AffineTransform::UnselectSide(p, q));
			}
		}
		if (s == 1) {
			this->reflect(x, y, z, t, p, q);
		}
		if (s == 0) {
			this->scalar(x, y, z, t, p, q);
		}
		if (s == 2) {
			//this->translate(x, y, z, t, p, q);
			if (!t) return;
			if (p != q) {
				m_models[t - 1].applyAT(AffineTransform::SelectSide(p, q));
			}
			m_models[t - 1].applyAT(AffineTransform::Translation(x, y, z));
			if (p != q) {
				m_models[t - 1].applyAT(AffineTransform::UnselectSide(p, q));
			}
		}
	}
	void rotate(double x, double y, double z, int t, Vector3D p = Vector3D(0, 0, 0), Vector3D q = Vector3D(0, 0, 0)) {
		if (!t) return;
		if (p != q) {
			m_models[t - 1].applyAT(AffineTransform::SelectSide(p, q));
		}
		m_models[t - 1].applyAT(AffineTransform::RotationX(x));
		m_models[t - 1].applyAT(AffineTransform::RotationY(y));
		m_models[t - 1].applyAT(AffineTransform::RotationZ(z));
		if (p != q) {
			m_models[t - 1].applyAT(AffineTransform::UnselectSide(p, q));
		}
	}
	void scalar(double x, double y, double z, int t, Vector3D p = Vector3D(0, 0, 0), Vector3D q = Vector3D(0, 0, 0)) {
		if (!t) return;
		if (p != q) {
			m_models[t - 1].applyAT(AffineTransform::SelectSide(p, q));
		}
		m_models[t - 1].applyAT(AffineTransform::Scaling(x, y, z));
		if (p != q) {
			m_models[t - 1].applyAT(AffineTransform::UnselectSide(p, q));
		}
	}
	void translate(double x, double y, double z, int t, Vector3D p = Vector3D(0, 0, 0), Vector3D q = Vector3D(0, 0, 0)) {
		if (!t) return;
		if (p != q) {
			m_models[t - 1].applyAT(AffineTransform::SelectSide(p, q));
		}
		m_models[t - 1].applyAT(AffineTransform::Translation(x, y, z));
		if (p != q) {
			m_models[t - 1].applyAT(AffineTransform::UnselectSide(p, q));
		}
	}
	void reflect(double x, double y, double z, int t, Vector3D p = Vector3D(0, 0, 0), Vector3D q = Vector3D(0, 0, 0)) {
		if (!t) return;
		if (p != q) {
			m_models[t - 1].applyAT(AffineTransform::SelectSide(p, q));
		}
		if (x) {
			if (y) {
				if (z) {
					m_models[t - 1].applyAT(AffineTransform::ReflectionO());
				}
				else {
					m_models[t - 1].applyAT(AffineTransform::ReflectionZ());
				}
			}
			else {
				if (z) {
					m_models[t - 1].applyAT(AffineTransform::ReflectionY());
				}
				else {
					m_models[t - 1].applyAT(AffineTransform::ReflectionYZ());
				}
			}
		}
		else {
			if (y) {
				if (z) {
					m_models[t - 1].applyAT(AffineTransform::ReflectionX());
				}
				else {
					m_models[t - 1].applyAT(AffineTransform::ReflectionZX());
				}
			}
			else {
				if (z) {
					m_models[t - 1].applyAT(AffineTransform::ReflectionXY());
				}
			}
		}
		if (p != q) {
			m_models[t - 1].applyAT(AffineTransform::UnselectSide(p, q));
		}
	}
};
