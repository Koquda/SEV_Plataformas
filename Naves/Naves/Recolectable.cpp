#include "Recolectable.h"

Recolectable::Recolectable(int x, int y, Game* game)
	: Actor("res/icono_recolectable.png", x, y, 40, 40, game)
{
	cout << "Recolectable creado" << endl;
}


void Recolectable::update() {
	vx = -1;
	x = x + vx;
}

