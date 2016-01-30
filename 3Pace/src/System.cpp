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

/*
* Check if the Components in the bag matches with the System's Components
* Returns true if the bag matches to the system, otherwise false
*/
bool System::componentCheck(ComponentBag& bag) {
	if (m_ComponentIDs.empty())
		return false;

	for (auto& id : m_ComponentIDs) {
		if (bag.find(id.second) == bag.end())
			return false;
	}

	return true;
}