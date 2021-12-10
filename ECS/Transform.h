#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "Vec3.h"
#include "Quat.h"

class Transform : public Component {
public:
	Transform() : position(Vec3::zero), rotation(Quat::identity), scale(Vec3::one) {};
	Transform(Vec3 pos, Quat rot, Vec3 scl) : position(pos), rotation(rot), scale(scl) {};

	Vec3 position;
	Quat rotation;
	Vec3 scale;

private:
	

};

#endif