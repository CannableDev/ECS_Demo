#ifndef QUAT_H
#define QUAT_H

#include "Vec3.h"
#include <iostream>
#include <array>

class Quat {
public:
	Quat();
	Quat(double x, double y, double z, double w);
	Quat(Vec3 v, double w);

	double Magnitude() const;
	Quat Normalize() const;
	static Quat Normalize(Quat q);

	double DotProd(const Quat other);
	static double DotProd(const Quat a, const Quat b);

	/**
	 * Returns the angle between two quaternions.
	 * The quaternions MUST be normalized.
	 */
	double AngleBetween(const Quat other);
	/**
	 * Returns the angle between two quaternions.
	 * The quaternions MUST be normalized.
	 */
	static double AngleBetween(const Quat a, const Quat b);

	/**
	 * Returns the conjugate of a quaternion.
	 * Inverts x, y, z.
	 */
	Quat Conjugate();
	/**
	 * Returns the conjugate of a quaternion.
	 * Inverts x, y, z.
	 */
	static Quat Conjugate(Quat r);

	/**
     * Creates a new quaternion from the angle-axis representation of
     * a rotation.
     * Requires Radians for angle
     */
	static Quat FromAngleAxis(double angle, Vec3 axis);

	std::array<double, 16> ToMatrix();

	/**
	 * Create a quaternion rotation which rotates "fromVector" to "toVector".
	 * @param fromVector: The vector from which to start the rotation.
	 * @param toVector: The vector at which to end the rotation.
	 */
	static Quat FromToRotation(Vec3 from, Vec3 to);
	
	Quat Inverse();
	static Quat Inverse(Quat rotation);
	
	static Quat Lerp(Quat a, Quat b, double t);
	static Quat LerpUnclamped(Quat a, Quat b, double t);
	
	/**
	 * Creates a rotation with the specified forward direction. This is the
	 * same as calling LookRotation with (0, 1, 0) as the upwards vector.
	 * The output is undefined for parallel vectors.
	 * @param forward: The forward direction to look toward.
	 * @return: A new quaternion.
	 */
	static Quat LookRotation(Vec3 forward);
	
	/**
	 * Creates a rotation with the specified forward and upwards directions.
	 * The output is undefined for parallel vectors.
	 * @param forward: The forward direction to look toward.
	 * @param upwards: The direction to treat as up.
	 * @return: A new quaternion.
	 */
	static Quat LookRotation(Vec3 forward, Vec3 upwards);
	
	static Quat FromTo(Vec3 source, Vec3 dest);

	static Quat Slerp(Quat a, Quat b, double t);
	static Quat FreeSlerp(Quat a, Quat b, double t);

	Quat RotateTowards(Quat to, double maxRadiansDelta);
	static Quat RotateTowards(Quat from, Quat to, double maxRadiansDelta);

	/**
	 * Outputs the angle axis representation of the provided quaternion.
	 * @param rotation: The input quaternion.
	 * @param angle: The output angle.
	 * @param axis: The output axis.
	 */
	static void ToAngleAxis(Quat rot, double& angle, Vec3& axis);

	Vec3 GetForwardVec();
	Vec3 GetUpVec();
	Vec3 GetLeftVec();

	Quat& operator+=(const double d);
	Quat& operator-=(const double d);
	Quat& operator*=(const double d);
	Quat& operator/=(const double d);
	Quat& operator+=(const Quat q);
	Quat& operator-=(const Quat q);
	Quat& operator*=(const Quat q);
	friend std::ostream& operator<<(std::ostream& os, const Quat& q);

	double w;
	double x;
	double y;
	double z;

	static const Quat identity;

};

inline Quat operator+(Quat q, const double d) { return q += d; }
inline Quat operator-(Quat q, const double d) { return q -= d; }
inline Quat operator*(Quat q, const double d) { return q *= d; }
inline Quat operator/(Quat q, const double d) { return q /= d; }
inline Quat operator+(const double d, Quat q) { return q += d; }
inline Quat operator-(const double d, Quat q) { return q -= d; }
inline Quat operator*(const double d, Quat q) { return q *= d; }
inline Quat operator/(const double d, Quat q) { return q /= d; }
inline Quat operator-(Quat q) { return q * -1; }

inline Quat operator+(Quat a, const Quat b)
{
	return a += b;
}
inline Quat operator-(Quat a, const Quat b)
{
	return a -= b;
}
inline Quat operator*(Quat a, const Quat b)
{
	return a *= b;
}

inline Vec3 operator*(Quat q, Vec3 v)
{
	Vec3 u = Vec3(q.x, q.y, q.z);
	double s = q.w;
	return u * (Vec3::DotProd(u, v) * 2) + v * (s * s - Vec3::DotProd(u, u)) + Vec3::CrossProd(u, v) * (2.0 * s);
}

inline bool operator==(const Quat a, const Quat b)
{
	return a.x == b.x &&
		a.y == b.y &&
		a.z == b.z &&
		a.w == b.w;
}

inline bool operator!=(const Quat a, const Quat b)
{
	return !(a == b);
}

#endif
