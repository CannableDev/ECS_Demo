#ifndef ENTITY_H
#define ENTITY_H

#include <map>

#include "ECS.h"
#include "Component.h"
#include "Transform.h"

class Entity {
public:
	Entity();
	Entity(Vec3 pos, Quat rot, Vec3 scl);
	virtual ~Entity();

	Transform* transform;

	template<typename T, typename... TArgs>
	inline T& add(TArgs&&... args);

	template<typename T>
	inline T& get() const;

	template<typename T>
	inline void remove();

	template<typename T>
	inline bool has();

	template<typename T, typename T2, typename... TArgs>
	inline bool has();

	virtual bool isAlive();
	virtual void kill();

	virtual void Update();

protected:
	friend class EntityManager;

	std::map<TypeID, Component*> components;
	bool alive;
};

template<typename T, typename ... TArgs>
inline T& Entity::add(TArgs && ... args)
{
	// Creates new component with its arguments for its constructor
	T* comp(new T(std::forward<TArgs>(args)...));

	// Checks to see if created successfully
	// init returns true by default, so objects that only need to construct and not init will return true
	if (comp->init()) {
		// Get a id based on the class type of component
		comp->id = getCompTypeID<T>();
		// insert into entities map of components
		components.emplace(comp->id, comp);
		comp->entity = this;
		return *comp;
	}

	// else returns a null 
	return *static_cast<T*>(nullptr);
}

template<typename T>
inline T& Entity::get() const
{
	// Grabs component from entity of type inserted
	auto ptr(components.at(getCompTypeID<T>()));
	return *static_cast<T*>(ptr);
}

// removes component if it exists on entity
template<typename T>
inline void Entity::remove() {

	T* comp = &get<T>();

	if (comp != nullptr) {
		components.erase(comp->id);
		delete comp;
	}
}

template<typename T>
inline bool Entity::has()
{
	return components.count(getCompTypeID<T>());
}

template<typename T, typename T2, typename... TArgs>
inline bool Entity::has() 
{
	return has<T>() && has<T2, TArgs...>();
}
#endif 