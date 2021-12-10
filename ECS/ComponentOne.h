#ifndef COMP_ONE_H
#define COMP_ONE_H

#include <iostream>

#include "Component.h"

class ComponentOne : public Component {
public:
	ComponentOne(float a, float b) : a(a), b(b) {};

	void Update() {
		
		Print();
		a++;
		b += 2;
	}
	
	void Print() {
		std::cout << "ComponentOne: " << this << " values " << a << " and " << b << std::endl;
	}

private:
	float a;
	float b;

};

#endif