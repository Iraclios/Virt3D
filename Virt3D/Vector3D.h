#pragma once
#include <math.h>
class Vector3D
{
	friend class Matrix;
	double x;
	double y;
	double z;
	double w;
public:
	Vector3D(double x, double y, double z) :
		x(x), y(y), z(z), w(1) {}
	Vector3D operator=(Vector3D& t) {
		x = t.x;
		y = t.y;
		z = t.z;
		w = t.w;
		return Vector3D(t.x, t.y, t.z);
	}
	Vector3D operator*(double t) {
		return Vector3D(t * x, t * y, t * z);
	}
	Vector3D operator/(double t) {
		return Vector3D(x / t, y / t, z / t);
	}
	double operator*(Vector3D& t) {
		return x * t.x + y * t.y + z * t.z;
	}
	Vector3D operator%(Vector3D& t) {
		return Vector3D(y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x);
	}
	Vector3D Normalize() {
		return *this / sqrt(*this * *this);
	}
	double getX() const {
		return x;
	}
	double getY() const {
		return y;
	}
	double getZ() const {
		return z;
	}
	bool operator==(Vector3D& t) {
		return (x == t.x) && (y == t.y) && (z == t.z) && (w == t.w);
	}
	bool operator!=(Vector3D& t) {
		return (x != t.x) || (y != t.y) || (z != t.z) || (w != t.w);
	}
};

