#include "Entity.h"

Entity::Entity() : alive(true)
{
	transform = &(add<Transform>());
}

Entity::Entity(Vec3 pos, Quat rot, Vec3 scl) : alive(true)
{
	transform = &(add<Transform>(pos, rot, scl));
}

Entity::~Entity()
{
	for (auto itr = components.begin(); itr != components.end(); itr++)
	{
		delete (itr->second);
	}
	components.clear();
}

bool Entity::isAlive()
{
	return alive;
}

void Entity::kill()
{
	alive = false;
}

void Entity::Update()
{
	for (auto& c : components) {
		c.second->Update();
	}
}