#include "Player.h"

Player::Player(float x, float y, int width, int height, string filename, Game* game)
	: Actor(filename, x, y, width, height, game) {
	audioShoot = Audio::createAudio("res/efecto_disparo.wav", false);
	bullets = 3;
}

void Player::update()
{
	if (shootTime > 0) {
		shootTime--;
	}

	
	
	if (x < 0) {
		x = 0;
	}

	if (x > WIDTH) {
		x = WIDTH;
	} 

	if (y < 0) {
		y = 0;
	}

	if (y > HEIGHT) {
		y = HEIGHT;
	}


	x = x + vx;
	y = y + vy;
	


}

void Player::moveX(float axis)
{
	vx = axis * velocity;
}

void Player::moveY(float axis)
{
	vy = axis * velocity;
}

Projectile* Player::shoot() {
	if (bullets > 0) {
		if (shootTime == 0) {
			bullets--;
			audioShoot->play();
			shootTime = shootCadence;
			return new Projectile(x, y, game);
		}
	}
	return NULL;
	
}

Player* Player::changePlayer1() {
	Player* newPlayer = new Player(x, y, 50, 57, "res/jugador.png", game);
	newPlayer->velocity = 3;
	newPlayer->shootCadence = 30;

	return newPlayer;
}


Player* Player::changePlayer2() {
	
	Player* newPlayer = new Player(x, y, 40, 17, "res/nave2.png", game);
	newPlayer->velocity = 5;
	newPlayer->shootCadence = 15;

	return newPlayer;
}

