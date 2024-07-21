#pragma once
#include "framework.h"
#include "AffineTransform.h"
class Camera3D
{
	Vector3D view;
	Vector3D kv;
	Vector3D iv;
	Vector3D jv;
	Matrix ViewCoordinates() {
		double T[16] = {
		iv.getX(), iv.getY(), iv.getZ(), -iv.getX() * view.getX() - iv.getY() * view.getY() - iv.getZ() * view.getZ(),
		jv.getX(), jv.getY(), jv.getZ(), -jv.getX() * view.getX() - jv.getY() * view.getY() - jv.getZ() * view.getZ(),
		kv.getX(), kv.getY(), kv.getZ(), -kv.getX() * view.getX() - kv.getY() * view.getY() - kv.getZ() * view.getZ(),
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	Matrix WorldCoordinates() {
		double T[16] = {
		iv.getX(), iv.getY(), iv.getZ(), view.getX(),
		jv.getX(), jv.getY(), jv.getZ(), view.getY(),
		kv.getX(), kv.getY(), kv.getZ(), view.getZ(),
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	Matrix Projection() {
		double T[12] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 1 };
		return Matrix(3, 4, T);
	}
public:
	Camera3D(Vector3D view, Vector3D normal, Vector3D vertical) :
		view(view), kv(normal.Normalize()), iv((normal% vertical).Normalize()), jv(kv% iv) {}
	Matrix projectionMatrix() {
		return Projection() * ViewCoordinates();
	}
};

