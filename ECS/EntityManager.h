#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include "Entity.h"

class EntityManager {
public:
	EntityManager();
	~EntityManager();

	static EntityManager* Get();
	
	void SetRunning(bool running);

	void Update();
	void Refresh();

	void Purge();

	std::vector<std::shared_ptr<Entity>>* GetEntities();

	void AddEntity(Entity* e);
	void AddNewEntities();
	void EraseEntity(Entity* e);
	void EraseEntity(unsigned int index);

private:
	EntityManager(EntityManager& other) = delete;
	void operator=(const EntityManager&) = delete;
	static EntityManager* instance;

	static bool running;


	std::vector<std::shared_ptr<Entity>> newEntities;
	std::vector<std::shared_ptr<Entity>> entities;

};

#endif