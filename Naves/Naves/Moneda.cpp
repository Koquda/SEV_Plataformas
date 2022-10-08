#include "Moneda.h"

Moneda::Moneda(int x, int y, Game* game)
	: Actor("res/moneda.png", x, y, 40, 40, game)
{
	cout << "Moneda creada" << endl;
}

