#pragma once
#include "Vector3D.h"
class Matrix
{
	int m;
	int n;
	double* data;
public:
	Matrix(int a, int b, double* t) {
		m = a;
		n = b;
		int s = m * n;
		data = new double[s];
		for (int i = 0; i < s; i++) data[i] = t[i];
	}
	Matrix(const Matrix& t) {
		m = t.m;
		n = t.n;
		int s = m * n;
		data = new double[s];
		for (int i = 0; i < s; i++) data[i] = t.data[i];
	}
	~Matrix() {
		delete[]data;
	}
	Matrix operator=(Matrix t) {
		m = t.m;
		n = t.n;
		int s = m * n;
		delete[]data;
		data = new double[s];
		for (int i = 0; i < s; i++) data[i] = t.data[i];
		return Matrix(m, n, data);
	}
	Matrix operator*(Matrix t) {
		double* r = new double[m * t.n];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < t.n; j++) {
				r[i * t.n + j] = 0;
				for (int k = 0; k < n; k++) r[i * t.n + j] += data[i * n + k] * t.data[k * t.n + j];
			}
		}
		return Matrix(m, t.n, r);
	}
	Matrix operator*=(const Matrix t) {
		double* r = new double[m * t.n];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < t.n; j++) {
				r[i] = 0;
				for (int k = 0; k < n; k++) r[i * m + j] += data[i * m + k] * t.data[k * n + j];
			}
		}
		n = t.n;
		return Matrix(m, t.n, r);
	}
	Vector3D operator*(Vector3D t) {
		Vector3D Result(0, 0, 0);
		Result.x = t.x * data[0] + t.y * data[1] + t.z * data[2] + t.w * data[3];
		Result.y = t.x * data[4] + t.y * data[5] + t.z * data[6] + t.w * data[7];
		Result.z = t.x * data[8] + t.y * data[9] + t.z * data[10] + t.w * data[11];
		Result.w = t.x * data[12] + t.y * data[13] + t.z * data[14] + t.w * data[15];
		Result.Normalize();
		return Result;
	}
	double getElement(int n) {
		return data[n];
	}
};