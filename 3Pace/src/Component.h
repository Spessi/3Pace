#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>
#include <bitset>
#include <stdexcept>


// Forward declaration
class Component;

typedef std::bitset<64> ComponentBitID;

// A bag to store Components according to their bitset
typedef std::unordered_map<ComponentBitID, std::shared_ptr<Component>> ComponentBag;

// Power of Two calculation for bitset mask
#define POWTWO(x) (1<<(x-1))

class Component {
public:
	enum class Types : std::uint64_t {
		INVALID		= 0,
		POSITION	= POWTWO(1),
		VELOCITY	= POWTWO(2),
		CAMERA		= POWTWO(3),
		MESH		= POWTWO(4),
		INPUT		= POWTWO(5),
		INTENT		= POWTWO(6),
	};
	Component();
	virtual ~Component();
	virtual ComponentBitID getID() = 0;

	static ComponentBitID bittify(Types type);
};

