#include "Bomba.h"

Bomba::Bomba(int x, int y, Game* game)
	: Actor("res/bomba.png", x, y, 45, 47, game)
{
	cout << "Bomba creada" << endl;
}


void Bomba::update() {
	
}
