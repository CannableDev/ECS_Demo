#ifndef MATHHELP_H
#define MATHHELP_H

#define M_PI 3.14159265358979323846
#define M_PI_2	1.57079632679489661923
#define SMALL_DOUBLE 0.0000000001

#include <cmath>

template<typename T>
inline T Lerp(T a, T b, double t) {
	return (a + ((b - a) * t));
};

template<typename T>
inline T LerpClamped(T a, T b, double t) {
	if (t > 1) t = 1;
	if (t < 0) t = 0;
	return (a + ((b - a) * t));
};

static inline double ToRadians(double in) {
	return in * M_PI / 180;
}

static inline double ToDegrees(double in) {
	return in * 180 / M_PI;
}

static inline float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
#endif
