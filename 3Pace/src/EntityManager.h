#pragma once

#include <map>
#include <stack>
#include <memory>
#include "Component.h"

typedef std::map<std::uint32_t, ComponentBag> Entities;

class EntityManager {
public:
	EntityManager();
	~EntityManager();
	void init();
	std::uint32_t createEntity();
	bool deleteEntity(std::uint32_t id);
	void addComponent(std::uint32_t entityID, Component* component);

	Entities& getEntities();
	ComponentBag& getEntity(std::uint32_t id);



private:
	Entities m_Entities;
	unsigned int m_UniqueID;
	std::stack<unsigned int> m_ReusableUniqueID;
};

