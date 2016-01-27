#pragma once

#include <bitset>
#include <map>
#include "Component.h"

class System {
public:
	System();
	virtual ~System();
	bool componentCheck(ComponentBag& bag);
	virtual void process(ComponentBag bag, float dt) = 0;
	void registerComponent(Component::Types id);
	std::shared_ptr<Component> getComponentFromBag(ComponentBag& bag, Component::Types id);

protected:
	std::map<Component::Types, ComponentBitID> m_ComponentIDs;
};

