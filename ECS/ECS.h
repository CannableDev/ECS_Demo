#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <iostream>

class Entity;
class Component;

using TypeID = std::size_t;

inline TypeID getUniqueTypeID() {
	static TypeID lastID = 0u;
	return lastID++;
}

// Gives a unique numerical id based on the class type
template<typename T>
inline TypeID getCompTypeID() noexcept {
	// will explode if object is not a component
	static_assert(std::is_base_of<Component, T>::value, "Error: Type not a Component");
	
	// not insta returning because we want it to be constant per type of component
	static const TypeID typeID = getUniqueTypeID();
	return typeID;
}

#endif