#include "Vec3.h"


const Vec3 Vec3::one(1, 1, 1);
const Vec3 Vec3::zero(0, 0, 0);
const Vec3 Vec3::up(0, 1, 0);
const Vec3 Vec3::down(0, -1, 0);
const Vec3 Vec3::left(-1, 0, 0);
const Vec3 Vec3::right(1, 0, 0);
const Vec3 Vec3::forward(0, 0, -1);
const Vec3 Vec3::backward(0, 0, 1);

Vec3::Vec3() 
{
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(const Vec3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vec3::Vec3(double x, double y, double z) 
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::~Vec3()
{
}

double Vec3::Magnitude() const
{
	// can return zeros
	return sqrt((x * x) + (y * y) + (z * z));
}

double Vec3::SqrMagnitude() const
{
	return x * x + y * y + z * z;
}

double Vec3::SqrMagnitude(const Vec3& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

void Vec3::ClampMagnitude(double d)
{
	*this = Normalize() * d;
}

Vec3 Vec3::Normalize() const
{
	double mag(Magnitude());
	if (mag == 0) return zero;
	return Vec3(x / mag, y / mag, z / mag);
}

Vec3 Vec3::Normalize(Vec3 v)
{
	double mag(v.Magnitude());
	if (mag == 0) return zero;
	return Vec3(v.x / mag, v.y / mag, v.z / mag);
}

double Vec3::Distance(const Vec3& other)
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

double Vec3::DotProd(const Vec3& other)
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

double Vec3::DotProd(const Vec3& a, const Vec3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

double Vec3::AngleBetween(const Vec3& other) 
{
	double rad = acos(DotProd(other) / (other.Magnitude() * Magnitude()));
	return rad * 180 / M_PI;
}

Vec3 Vec3::CrossProd(const Vec3& other)
{
	return Vec3((y * other.z) - (z * other.y), (z * other.x) - (x * other.z), (x * other.y) - (y * other.x));
}

Vec3 Vec3::CrossProd(const Vec3& a, const Vec3& b)
{
	return Vec3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
}

Vec3 Vec3::Ortho()
{
	return (z < x) ? Vec3(y, -x, 0) : Vec3(0, -z, y);
}

Vec3 Vec3::Ortho(Vec3 v)
{
	return (v.z < v.x) ? Vec3(v.y, -v.x, 0) : Vec3(0, -v.z, v.y);
}

Vec3 Vec3::Rotate(Vec3 rot)
{
	return Rotate(rot.x, rot.y, rot.z);
}

Vec3 Vec3::Rotate(double rotx, double roty, double rotz)
{
	rotx = rotx * M_PI / 180.0;
	roty = roty * M_PI / 180.0;
	rotz = rotz * M_PI / 180.0;

	Vec3 t(x, y, z);
	Vec3 result(x, y, z);

	if (rotx)
	{
		result.y = (t.y * cos(rotx) - t.z * sin(rotx));
		result.z = (t.y * sin(rotx) + t.z * cos(rotx));

		t.y = result.y;
		t.z = result.z;
	}

	if (roty)
	{
		result.x = (t.x * cos(roty) + t.z * sin(roty));
		result.z = (-t.x * sin(roty) + t.z * cos(roty));

		t.x = result.x;
		t.z = result.z;
	}

	if (rotz)
	{
		result.x = (t.x * cos(rotz) - t.y * sin(rotz));
		result.y = (t.x * sin(rotz) + t.y * cos(rotz));
	}

	if (result.x < VEC_MIN && result.x > -VEC_MIN) result.x = 0;
	if (result.y < VEC_MIN && result.y > -VEC_MIN) result.y = 0;
	if (result.z < VEC_MIN && result.z > -VEC_MIN) result.z = 0;

	return result;
}

Vec3& Vec3::ApplyRotation(Vec3 rot)
{
	return ApplyRotation(rot.x, rot.y, rot.z);
}

Vec3& Vec3::ApplyRotation(double rotx, double roty, double rotz)
{
	rotx = rotx * M_PI / 180.0;
	roty = roty * M_PI / 180.0;
	rotz = rotz * M_PI / 180.0;

	Vec3 t(x, y, z);

	if (rotx)
	{
		y = (t.y * cos(rotx) - t.z * sin(rotx));
		z = (t.y * sin(rotx) + t.z * cos(rotx));

		t.y = y;
		t.z = z;
	}

	if (roty)
	{
		x = (t.x * cos(roty) + t.z * sin(roty));
		z = (-t.x * sin(roty) + t.z * cos(roty));

		t.x = x;
		t.z = z;
	}

	if (rotz)
	{
		x = (t.x * cos(rotz) - t.y * sin(rotz));
		y = (t.x * sin(rotz) + t.y * cos(rotz));
	}

	if (x < VEC_MIN && x > -VEC_MIN) x = 0;
	if (y < VEC_MIN && y > -VEC_MIN) y = 0;
	if (z < VEC_MIN && z > -VEC_MIN) z = 0;

	return *this;
}

std::array<double, 3> Vec3::toArray()
{
	return { x, y, z };
}

Vec3 Vec3::Lerp(Vec3 v1, Vec3 v2, const double& time)
{
	return Vec3(v1 + ((v2 - v1) * time));
}

Vec3 Vec3::operator* (const double d)
{
	return Vec3(x * d, y * d, z * d);
}

Vec3 Vec3::operator/ (const double d)
{
	return Vec3(x / d, y / d, z / d);
}

Vec3 Vec3::operator+ (const Vec3& other)
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator- (const Vec3& other)
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3& Vec3::operator*=(double d)
{
	x *= d;
	y *= d;
	z *= d;
	return *this;
}

Vec3& Vec3::operator/=(double d)
{
	x /= d;
	y /= d;
	z /= d;
	return *this;
}

Vec3& Vec3::operator+=(double d)
{
	x += d;
	y += d;
	z += d;
	return *this;
}

Vec3& Vec3::operator-=(double d)
{
	x -= d;
	y -= d;
	z -= d;
	return *this;
}

Vec3& Vec3::operator*=(const Vec3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

Vec3& Vec3::operator/=(const Vec3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}

Vec3& Vec3::operator+=(const Vec3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vec3 Vec3::operator-()
{
	return Vec3(-x, -y, -z);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	os << "(" << std::to_string(v.x) << ", " << std::to_string(v.y) << ", " << std::to_string(v.z) << ")";
	return os;
}
