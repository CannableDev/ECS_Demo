#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
public:
	virtual ~Component() {};

	size_t id;
	Entity* entity;

	virtual bool init() { return true; }
	virtual void Update() {};

private:


};

#endif