#pragma once

#include "Actor.h"

class Recolectable : public Actor
{
public:
	Recolectable(int x, int y, Game* game);
	void update();
};

