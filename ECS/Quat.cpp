#include "Quat.h"

const Quat Quat::identity(0, 0, 0, 1);

Quat::Quat() : x(0), y(0), z(0), w(1)
{
}

Quat::Quat(double x, double y, double z, double w) : x(x), y(y), z(z), w(w)
{
}

Quat::Quat(Vec3 v, double w) : x(v.x), y(v.y), z(v.z), w(w)
{
}

double Quat::Magnitude() const
{
	return sqrt(w*w + x*x + y*y + z*z);
}

Quat Quat::Normalize() const
{
	return *this / Magnitude();
}

Quat Quat::Normalize(Quat q)
{
	return q / q.Magnitude();
}

double Quat::DotProd(const Quat other)
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

double Quat::DotProd(const Quat a, const Quat b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

double Quat::AngleBetween(const Quat other)
{
	double dot = DotProd(other);
	return acos(fmin(fabs(dot), 1)) * 2;
}

double Quat::AngleBetween(const Quat a, const Quat b)
{
	double dot = DotProd(a, b);
	return acos(fmin(fabs(dot), 1)) * 2;
}

Quat Quat::Conjugate()
{
	return Quat(-x, -y, -z, w);
}

Quat Quat::Conjugate(Quat r)
{
	return Quat(-r.x, -r.y, -r.z, r.w);
}

// WORLD ROT
// FromAngleAxis * rotation = new rotation
// LOCAL ROT
// rotation * FromAngleAxis = new rotation
Quat Quat::FromAngleAxis(double angle, Vec3 axis)
{
	angle = ToRadians(angle);
	double mag = axis.Magnitude();
	double s = sin(angle * 0.5) / mag;
	
	return Quat(axis.x * s, axis.y * s, axis.z * s, cos(angle * 0.5));;
}

// to give to opengl via glMultMatrix
std::array<double, 16> Quat::ToMatrix() {
	
	return {
		1 - 2 * (z * z + y * y), 2 * (x * y + w * z), 2 * (z * x - w * y), 0,
		2 * (x * y - w * z), 1 - 2 * (x * x + z * z), 2 * (y * z + w * x), 0,
		2 * (z * x + w * y), 2 * (y * z - w * x), 1 - 2 * (x * x + y * y), 0,
		0,                   0,                   0,                       1
	};
}

Quat Quat::FromToRotation(Vec3 from, Vec3 to)
{
	double dot = Vec3::DotProd(from, to);
	double k = sqrt(Vec3::SqrMagnitude(from) * Vec3::SqrMagnitude(to));
	if (fabs(dot / k + 1) < 0.00001)
	{
		Vec3 ortho = Vec3::Ortho(from);
		return Quat(Vec3::Normalize(ortho), 0);
	}

	Vec3 cross = Vec3::CrossProd(from, to);
	return Normalize(Quat(cross, dot + k));
}

Quat Quat::Inverse()
{
	double m = Magnitude();
	return Conjugate() / (m * m);
}

Quat Quat::Inverse(Quat rotation)
{
	double m = rotation.Magnitude();
	return Conjugate(rotation) / (m * m);
}

Quat Quat::Lerp(Quat a, Quat b, double t)
{
	if (t < 0) return Normalize(a);
	else if (t > 1) return Normalize(b);
	return LerpUnclamped(a, b, t);
}

Quat Quat::LerpUnclamped(Quat a, Quat b, double t)
{
	Quat quaternion;
	if (DotProd(a, b) >= 0)
		quaternion = a * (1 - t) + b * t;
	else
		quaternion = a * (1 - t) - b * t;
	return Normalize(quaternion);
}

Quat Quat::LookRotation(Vec3 forward)
{
	return LookRotation(forward, Vec3::up);
}

Quat Quat::LookRotation(Vec3 forward, Vec3 upwards)
{
	Quat rot1 = Quat::FromTo(Vec3::forward, forward);

	Vec3 up = rot1 * upwards;
	Quat rot2 = Quat::FromTo(Vec3::up, upwards);

	return rot2 * rot1;
}

Quat Quat::FromTo(Vec3 source, Vec3 dest)
{
	double angle = source.AngleBetween(dest);
	Vec3 axis = source.CrossProd(dest);

	return Quat::FromAngleAxis(angle, axis);
}

Quat Quat::Slerp(Quat a, Quat b, double t)
{
	if (t < 0) return a.Normalize();
	else if (t > 1) return b.Normalize();
	return FreeSlerp(a, b, t);
}

Quat Quat::FreeSlerp(Quat a, Quat b, double t)
{
	double n1;
	double n2;
	double n3 = DotProd(a, b);
	bool flag = false;
	if (n3 < 0)
	{
		flag = true;
		n3 = -n3;
	}
	if (n3 > 0.999999)
	{
		n2 = 1 - t;
		n1 = flag ? -t : t;
	}
	else
	{
		double n4 = acos(n3);
		double n5 = 1 / sin(n4);
		n2 = sin((1 - t) * n4) * n5;
		n1 = flag ? -sin(t * n4) * n5 : sin(t * n4) * n5;
	}
	Quat q;
	q.x = (n2 * a.x) + (n1 * b.x);
	q.y = (n2 * a.y) + (n1 * b.y);
	q.z = (n2 * a.z) + (n1 * b.z);
	q.w = (n2 * a.w) + (n1 * b.w);
	return q.Normalize();
}

Quat Quat::RotateTowards(Quat to, double maxRadiansDelta)
{
	double angle = AngleBetween(to);
	if (angle == 0)
		return to;
	maxRadiansDelta = fmax(maxRadiansDelta, angle - M_PI);
	double t = fmin(1, maxRadiansDelta / angle);
	return Quat::FreeSlerp(*this, to, t);
}

Quat Quat::RotateTowards(Quat from, Quat to, double maxRadiansDelta)
{
	double angle = Quat::AngleBetween(from, to);
	if (angle == 0)
		return to;
	maxRadiansDelta = fmax(maxRadiansDelta, angle - M_PI);
	double t = fmin(1, maxRadiansDelta / angle);
	return Quat::FreeSlerp(from, to, t);
}

void Quat::ToAngleAxis(Quat rot, double& angle, Vec3& axis)
{
	if (rot.w > 1)
		rot = rot.Normalize();
	angle = 2 * acos(rot.w);
	double s = sqrt(1 - rot.w * rot.w);
	if (s < SMALL_DOUBLE) {
		axis.x = 1;
		axis.y = 0;
		axis.z = 0;
	}
	else {
		axis.x = rot.x / s;
		axis.y = rot.y / s;
		axis.z = rot.z / s;
	}
}

Vec3 Quat::GetForwardVec()
{
	Quat pure(Vec3::forward, 0);
	std::cout << "Pure " << pure << std::endl;
	std::cout << "Conj " << Conjugate() << std::endl;
	Quat right = pure * Conjugate();
	std::cout << "This Rot " << *this << std::endl;
	std::cout << "Right " << right << std::endl;
	Quat left = *this * right;
	std::cout << "Left " << left << std::endl;
	return Vec3(left.x, left.y, left.z);
}

Vec3 Quat::GetUpVec()
{
	Quat pure(Vec3::forward, 0);
	Quat right = pure * Conjugate();
	Quat left = *this * right;
	return Vec3(left.x, left.y, left.z);
}

Vec3 Quat::GetLeftVec()
{
	Quat pure(Vec3::left, 0);
	Quat right = pure * Conjugate();
	Quat left = *this * right;
	return Vec3(left.x, left.y, left.z);
}

/****OPERATORS****/
Quat& Quat::operator+=(const double d)
{
	x += d;
	y += d;
	z += d;
	w += d;
	return *this;
}

Quat& Quat::operator-=(const double d)
{
	x -= d;
	y -= d;
	z -= d;
	w -= d;
	return *this;
}

Quat& Quat::operator*=(const double d)
{
	x *= d;
	y *= d;
	z *= d;
	w *= d;
	return *this;
}

Quat& Quat::operator/=(const double d)
{
	x /= d;
	y /= d;
	z /= d;
	w /= d;
	return *this;
}

Quat& Quat::operator+=(const Quat q)
{
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;
	return *this;
}

Quat& Quat::operator-=(const Quat q)
{
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;
	return *this;
}

Quat& Quat::operator*=(const Quat q)
{
	Quat nq;
	nq.w = w * q.w - x * q.x - y * q.y - z * q.z;
	nq.x = x * q.w + w * q.x + y * q.z - z * q.y;
	nq.y = w * q.y - x * q.z + y * q.w + z * q.x;
	nq.z = w * q.z + x * q.y - y * q.x + z * q.w;
	*this = nq;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Quat& q)
{
	os << "(" << std::to_string(q.x) << ", " << std::to_string(q.y) << ", " << std::to_string(q.z) << ", " << std::to_string(q.w) << ") Mag: " << q.Magnitude();
	return os;
}