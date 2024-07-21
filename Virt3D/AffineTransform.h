#pragma once
#include "Matrix.h"
#include <math.h>
#include "Vector3D.h"
class AffineTransform
{
public:
	static Matrix Identity3D()
	{
		double I[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, I);
	}
	static Matrix Translation(double x, double y, double z)
	{
		double T[16] = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix RotationY(double r) {
		double T[16] = {
		cos(r), 0, sin(r), 0,
		0, 1, 0, 0,
		-sin(r), 0, cos(r), 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix RotationX(double r) {
		double T[16] = {
		1, 0, 0, 0,
		0, cos(r), -sin(r), 0,
		0, sin(r), cos(r), 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix RotationZ(double r) {
		double T[16] = {
		cos(r), -sin(r), 0, 0,
		sin(r), cos(r), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix SelectSide(Vector3D p, Vector3D q) {
		double a = q.getX() - p.getX();
		double b = q.getY() - p.getY();
		double c = q.getZ() - p.getZ();
		double r = sqrt(b * b + c * c);
		double s = sqrt(a * a + b * b + c * c);
		double T[16] = {
		1, 0, 0, -p.getX(),
		0, 1, 0, -p.getY(),
		0, 0, 1, -p.getZ(),
		0, 0, 0, 1 };
		if (c == 0 && b == 0) return Matrix(4, 4, T);
		double T1[16] = {
		1, 0, 0, 0,
		0, b / r, c / r, 0,
		0, -c / r, b / r, 0,
		0, 0, 0, 1 };
		double T2[16] = {
		a / s, r / s, 0, 0,
		-r / s, a / s, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T2) * Matrix(4, 4, T1) * Matrix(4, 4, T);
	}
	static Matrix UnselectSide(Vector3D p, Vector3D q) {
		double a = q.getX() - p.getX();
		double b = q.getY() - p.getY();
		double c = q.getZ() - p.getZ();
		double r = sqrt(b * b + c * c);
		double s = sqrt(a * a + b * b + c * c);
		double T[16] = {
		1, 0, 0, p.getX(),
		0, 1, 0, p.getY(),
		0, 0, 1, p.getZ(),
		0, 0, 0, 1 };
		if (c == 0 && b == 0) return Matrix(4, 4, T);
		double T1[16] = {
		1, 0, 0, 0,
		0, b / r, -c / r, 0,
		0, c / r, b / r, 0,
		0, 0, 0, 1 };
		double T2[16] = {
		a / s, -r / s, 0, 0,
		r / s, a / s, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T) * Matrix(4, 4, T1) * Matrix(4, 4, T2);
	}
	static Matrix Scaling(double x, double y, double z)
	{
		double T[16] = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix ReflectionYZ() {
		double T[16] = {
		-1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix ReflectionZX() {
		double T[16] = {
		1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix ReflectionXY() {
		double T[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, -1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix ReflectionX() {
		double T[16] = {
		1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, -1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix ReflectionY() {
		double T[16] = {
		-1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, -1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix ReflectionZ() {
		double T[16] = {
		-1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
	static Matrix ReflectionO() {
		double T[16] = {
		-1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, -1, 0,
		0, 0, 0, 1 };
		return Matrix(4, 4, T);
	}
};

