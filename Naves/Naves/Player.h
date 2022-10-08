#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Audio.h"

class Player : public Actor
{
public:
	Player(float x, float y, int width, int height, string filename, Game* game);
	Projectile* shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	Player* changePlayer1();
	Player* changePlayer2();
	Audio* audioShoot;
	int shootCadence = 30;
	int shootTime = 0;
	int bullets = 0;
	int velocity = 3;

};
