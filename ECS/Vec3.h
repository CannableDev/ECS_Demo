#ifndef VEC_3_H
#define VEC_3_H

#include <math.h>
#include "MathHelp.h"
#include <string>
#include <iostream>
#include <array>

#define VEC_MIN 0.0000000001

class Vec3 {
public:
	Vec3();
	Vec3(const Vec3& other);
	Vec3(double x, double y, double z);
	~Vec3();

	double Magnitude() const;
	double SqrMagnitude() const;
	static double SqrMagnitude(const Vec3& v);
	void ClampMagnitude(double d);

	Vec3 Normalize() const;
	static Vec3 Normalize(Vec3 v);

	double Distance(const Vec3& other);

	double DotProd(const Vec3& other);
	static double DotProd(const Vec3& a, const Vec3& b);

	double AngleBetween(const Vec3& other);

	Vec3 CrossProd(const Vec3& other);
	static Vec3 CrossProd(const Vec3& a, const Vec3& b);

	Vec3 Ortho();
	static Vec3 Ortho(Vec3 v);

	Vec3 Rotate(Vec3 rot);
	Vec3 Rotate(double rotx, double roty, double rotz);
	Vec3& ApplyRotation(Vec3 rot);
	Vec3& ApplyRotation(double rotx, double roty, double rotz);

	std::array<double, 3> toArray();

	static Vec3 Lerp(Vec3 v1, Vec3 v2, const double& time);

	friend std::ostream& operator<<(std::ostream& os, const Vec3& v);

	Vec3 operator* (const double d);
	Vec3 operator/ (const double d);
	Vec3 operator+ (const Vec3& other);
	Vec3 operator- (const Vec3& other);
	Vec3& operator*=(double d);
	Vec3& operator/=(double d);
	Vec3& operator+=(double d);
	Vec3& operator-=(double d);
	Vec3& operator*=(const Vec3& other);
	Vec3& operator/=(const Vec3& other);
	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);
	Vec3 operator-();

	static const Vec3 one;
	static const Vec3 zero;
	static const Vec3 up;
	static const Vec3 down;
	static const Vec3 left;
	static const Vec3 right;
	static const Vec3 forward;
	static const Vec3 backward;

	double x;
	double y;
	double z;
};

inline Vec3 operator+(const double d, Vec3 v) { return v += d; }
inline Vec3 operator-(const double d, Vec3 v) { return v -= d; }
inline Vec3 operator*(const double d, Vec3 v) { return v *= d; }
inline Vec3 operator/(const double d, Vec3 v) { return v /= d; }

#endif    