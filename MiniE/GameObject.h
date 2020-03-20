#pragma once
#include <bitset> 
#include "Primitives.h"

class GameObject {
	std::hash<std::u32string> mystdhash;
	int ID;
	std::u32string Name;
		
public:
	GameObject(std::u32string N) {
		ID = mystdhash(N);
		Name = N;
	}
	~GameObject();

};