#include "EntityManager.h"
#include <memory>


EntityManager::EntityManager() {
	m_UniqueID = 1;
	m_Entities.clear();
}


EntityManager::~EntityManager() {
}

void EntityManager::init() {

}

std::uint32_t EntityManager::createEntity() {
	std::uint32_t id = 1;

	if (m_ReusableUniqueID.empty()) {
		id = m_UniqueID++;
	}
	else {
		id = m_ReusableUniqueID.top();
		m_ReusableUniqueID.pop();
	}

	// Create new Entity with empty Component 'bag'
	m_Entities.emplace(id, ComponentBag());

	return id;
}

bool EntityManager::deleteEntity(std::uint32_t id) {
	if (m_Entities.erase(id) > 0)
		return true;

	return false;
}

void EntityManager::addComponent(std::uint32_t entityID, Component* component) {
	m_Entities.at(entityID).emplace(component->getID(), std::unique_ptr<Component>(component));
}

Entities& EntityManager::getEntities() {
	return m_Entities;
}

ComponentBag& EntityManager::getEntity(std::uint32_t id) {
	return m_Entities.at(id);
}