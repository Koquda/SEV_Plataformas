#pragma once

#include "Actor.h"

class Bomba: public Actor
{
public:
	Bomba(int x, int y, Game * game);
	void update();
};