#ifndef COMP_TWO_H
#define COMP_TWO_H

#include <iostream>

#include "ComponentOne.h"

class ComponentTwo : public Component {
public:
	ComponentTwo(float a, float b) : a(a), b(b), one(new ComponentOne(999, 999)) {};
	ComponentTwo(float a, float b, ComponentOne* one) : a(a), b(b), one(one) {};

	void Update() {
		std::cout << "COMPONENTTWO: " << this << " values: " << a << " and " << b << " and comp one: " << std::endl << "------";
		one->Print();

		a--;
		b -= 0.5f;
	}

private:
	ComponentOne* one;
	float a;
	float b;

};

#endif