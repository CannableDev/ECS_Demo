#include <iostream>

#include "EntityManager.h"

#include "ComponentOne.h"
#include "ComponentTwo.h"

int main()
{
	EntityManager* manager = new EntityManager();

	Entity* first = new Entity(Vec3(1,2,3), Quat(0,0,0,1), Vec3(1,1,1));

	ComponentOne* compOne = &first->add<ComponentOne>(3, 5);
	first->add<ComponentTwo>(7, 9, compOne);

	std::cout << "Transform Component ID: " << first->get<Transform>().id << std::endl;
	std::cout << "ComponentOne ID: " << first->get<ComponentOne>().id << std::endl;
	std::cout << "ComponentTwo ID: " << first->get<ComponentTwo>().id << std::endl;

	std::cout << "First Transform: " << first->get<Transform>().position << std::endl;
	std::cout << "First Rotation: " << first->get<Transform>().rotation << std::endl;
	std::cout << "First Scale: " << first->get<Transform>().scale<< std::endl;
	std::cout << "First Has ComponentOne: " << first->has<ComponentOne>() << std::endl;
	std::cout << "First Has ComponentTwo: " << first->has<ComponentTwo>() << std::endl;

	first->Update();
	first->Update();
	first->Update();
	
	std::cout << "Removing ComponentTwo from First" << std::endl;
	first->remove<ComponentTwo>();

	std::cout << "First Has ComponentTwo: " << first->has<ComponentTwo>() << std::endl;

	first->Update();
	first->Update();
	first->Update();

	Entity* second = new Entity(Vec3(1, 2, 3), Quat(0, 0, 0, 1), Vec3(1, 1, 1));
	compOne = &second->add<ComponentOne>(3, 5);
	second->add<ComponentTwo>(7, 9, compOne);

	Entity* third = new Entity(Vec3(1, 2, 3), Quat(0, 0, 0, 1), Vec3(1, 1, 1));
	third->add<ComponentOne>(3, 5);

	manager->AddEntity(first);
	manager->AddEntity(second);
	manager->AddEntity(third);

	manager->Refresh();
	manager->AddNewEntities();

	manager->Update();
	manager->Update();
	manager->Update();

	second->kill();

	manager->Update();
	manager->Update();
	manager->Update();

	manager->Purge();

	delete manager;
}