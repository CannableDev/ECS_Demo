#include "EntityManager.h"

EntityManager* EntityManager::instance = nullptr;
bool EntityManager::running = true;

EntityManager::EntityManager()
{
	if (instance != nullptr) { delete this; }
	else instance = this;
	
	running = true;
}

EntityManager::~EntityManager()
{
	if (instance == this)
		instance = nullptr;
}

EntityManager* EntityManager::Get()
{
	if (instance == nullptr) new EntityManager();
	return instance;
}

void EntityManager::SetRunning(bool running)
{
	this->running = running;
}

void EntityManager::Update()
{
	if (!running) return;

	for (auto& e : entities) e->Update();

	Refresh();
	AddNewEntities();
}

void EntityManager::Refresh()
{
	int counter = 0;

	for (int i = 0; i < entities.size() - counter; i++) 
		if (!entities[i]->isAlive()) { 
			std::cout << "Killing entity " << entities[i] << std::endl;
			std::swap(entities[i], entities[entities.size() - 1 - counter]);
			counter++;
		}
	
	entities.erase(entities.end() - counter, entities.end());
}

void EntityManager::Purge()
{
	for (auto& e : entities) e->alive = false;
	newEntities.clear();
	running = false;
}

std::vector<std::shared_ptr<Entity>>* EntityManager::GetEntities()
{
	return &entities;
}

void EntityManager::AddEntity(Entity* e)
{
	std::shared_ptr<Entity> ptr(e);
	newEntities.push_back(ptr);
}

void EntityManager::EraseEntity(Entity* e)
{
	for (int i = 0; i < entities.size(); i++) {
		if (e == entities[i].get()) {
			entities.erase(entities.begin() + i);
			break;
		}
	}
}

void EntityManager::EraseEntity(unsigned int index)
{
	entities.erase(entities.begin() + index);
}

void EntityManager::AddNewEntities()
{
	for (auto& e : newEntities) {
		entities.push_back(e);
	}

	newEntities.clear();
}
