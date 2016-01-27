#include "System.h"



System::System() {
}


System::~System() {
}

void System::registerComponent(Component::Types id) {
	m_ComponentIDs.emplace(id, Component::bittify(id));
}

std::shared_ptr<Component> System::getComponentFromBag(ComponentBag& bag, Component::Types id) {
	return bag.at(m_ComponentIDs.at(id));
}

bool System::componentCheck(ComponentBag& bag) {
	if (m_ComponentIDs.empty())
		return false;

	for (auto& id : m_ComponentIDs) {
		try {
			bag.at(id.second);
		}
		catch (const std::out_of_range&) {
			return false;
		}
	}

	return true;
}