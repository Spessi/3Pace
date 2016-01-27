#pragma once

#include "System.h"
#include "EntityManager.h"
#include <vector>
#include <memory>

class SystemManager {
public:
	SystemManager();
	~SystemManager();
	void registerSystem(System* sys);
	void process(Entities& entities, float dt);

private:
	std::vector<std::shared_ptr<System>> m_Systems;
};

