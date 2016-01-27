#include "Component.h"

Component::Component() {
}


Component::~Component() {
	std::cout << "Component::~Component" << std::endl;
}

ComponentBitID Component::bittify(Types type) {
	return ComponentBitID(static_cast<std::uint64_t>(type));
}