#pragma once

#include "Layer.h"
#include "Text.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Audio.h"
#include "Recolectable.h"
#include "Moneda.h"
#include "Bomba.h"

#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	int newEnemyTime = 0;
	int newRecolectableTime = 0;
	int newBombaTime = 0;
	int newMonedaTime = 0;

	Player* player;
	Background* background;
	Actor* backgroundPoints; // Los puntos que van a salir en la pantalla
	int points;


	Audio* audioBackground;
	Text* textPoints;

	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<Recolectable*> recolectables;
	list<Bomba*> bombas;
	list<Moneda*> monedas;


};
