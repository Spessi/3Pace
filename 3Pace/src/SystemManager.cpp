#include "SystemManager.h"



SystemManager::SystemManager() {
}


SystemManager::~SystemManager() {
}


void SystemManager::registerSystem(System* sys) {
	m_Systems.push_back(std::shared_ptr<System>(sys));
}

void SystemManager::process(Entities& entities, float dt) {
	for (auto& system : m_Systems) {
		for (auto& entity : entities) {
			system->process(entity.second, dt);
		}
	}
}