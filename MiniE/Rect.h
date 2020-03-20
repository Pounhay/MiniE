#pragma once
#include "GameObject.h"

class Rect : GameObject {
	int x;
	int y;

public:

	Rect(std::u32string N, int X, int Y) : GameObject(N) {
		x = X;
		y = Y;

	}
	~Rect();

	void HandleEvents()
	{

	}

	void Update(int x1, int y1)
	{
		x += x1;
		y += y1;
	}

	void Render()
	{

	}

	


};
