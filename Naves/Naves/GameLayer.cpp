#include "GameLayer.h"

#include <unordered_set>



GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	player = new Player(50, 50, 50, 57, "res/jugador.png", game);
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);


	audioBackground = Audio::createAudio("res/musica_ambiente.mp3", true);
	audioBackground->play();


	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92f, HEIGHT * 0.04f, game);
	textPoints->content = to_string(points);
	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);


	projectiles.clear(); // Vaciar por si reiniciamos el juego

	recolectables.clear();

	bombas.clear();

	monedas.clear();

	enemies.clear(); // Vaciar por si reiniciamos el juego
	enemies.push_back(new Enemy(300, 50, game));
	enemies.push_back(new Enemy(300, 200, game));
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);

	}
	//procesar controles
	// Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}
}


void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			player = player->changePlayer1();
			break;
		case SDLK_2:
			player = player->changePlayer2();
			break;
		case SDLK_4:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}
	}

}

void GameLayer::update() {
	background->update();


	// Generar enemigos
	newEnemyTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		enemies.push_back(new Enemy(rX, rY, game));
		newEnemyTime = 110;
	}

	// Generar recolectables
	newRecolectableTime--;
	if (newRecolectableTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		recolectables.push_back(new Recolectable(rX, rY, game));
		newRecolectableTime = 1000;
	}

	// Generar bombas, arreglar las coordenadas, tienen que ser menores los valores
	newBombaTime--;
	if (newBombaTime <= 0) {
		int rX = (rand() % (480 - 40)) + 1 + 40;
		int rY = (rand() % (320 - 40)) + 1 + 40;
		bombas.push_back(new Bomba(rX, rY, game));
		newBombaTime = 2000;
	}

	// Generar monedas, arreglar las coordenadas, tienen que ser menores los valores
	newMonedaTime--;
	if (newMonedaTime <= 0) {
		int rX = (rand() % (480 - 40)) + 1 + 40;
		int rY = (rand() % (320 - 40)) + 1 + 40;
		monedas.push_back(new Moneda(rX, rY, game));
		newMonedaTime = 1000;
	}


	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	for (auto const& recolectable : recolectables) {
		recolectable->update();
	}
	for (auto const& bomba : bombas) {
		bomba->update();
	}

	// Colisiones, mirar si sigue siendo necesario este for
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			cout << "La cagaste manin" << endl;
			init();
			return; // Cortar el for
		}
	}


	// Colisiones , Enemy - Projectile

	std::unordered_set<Enemy*> deleteEnemies;
	std::unordered_set<Projectile*> deleteProjectiles;
	std::unordered_set<Recolectable*> deleteRecolectables;
	std::unordered_set<Bomba*> deleteBombas;
	std::unordered_set<Moneda*> deleteMonedas;


	// Colisiones, Player - Recolectable
	for (auto const& recolectable : recolectables) {
		if (player->isOverlap(recolectable)) {
			cout << "Pillaste un recolectable pa" << endl;
			player->bullets += 10;
			recolectables.remove(recolectable);
			return; // Cortar el for
		}
	}

	// Colisiones, Player - Bombas
	for (auto const& bomba : bombas) {
		if (player->isOverlap(bomba)) {
			cout << "Pillaste una bomba pa" << endl;
			for (auto const& enemy : enemies) {
				player->bullets++;
				points++;
			}
			textPoints->content = std::to_string(points);
			enemies.clear();
			bombas.remove(bomba);
			return; // Cortar el for
		}
	}
	 
	// Colisiones, Player - Monedas
	for (auto const& moneda : monedas) {
		if (player->isOverlap(moneda)) {
			cout << "Pillaste una moneda pa" << endl;
			points++;
			textPoints->content = std::to_string(points);
			monedas.remove(moneda);
			return; // Cortar el for
		}
	}

	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.emplace(projectile);
			}
		}
	}


	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				enemy->looseLife();
				deleteProjectiles.emplace(projectile);
				if (enemy->lifes == 0) {
					deleteEnemies.emplace(enemy);

					player->bullets++;
					points++;
					textPoints->content = std::to_string(points);
				}


				/*
				* Esto es para hacerlo con una lista pero es mucho mas eficiente
				* con un set porque el set es O(1)
				* 
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();

				if (!eInList) {
					deleteEnemies.push_back(enemy);
				}*/
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
	}
	deleteProjectiles.clear();

	for (auto const& delBomba : deleteBombas) {
		bombas.remove(delBomba);
	}
	deleteBombas.clear();

	for (auto const& delMoneda : deleteMonedas) {
		monedas.remove(delMoneda);
	}
	deleteBombas.clear();



	//wdcout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();

	for (auto const& bomba : bombas) {
		bomba->draw();
	}

	for (auto const& moneda : monedas) {
		moneda->draw();
	}

	for (auto const& recolectable : recolectables) {
		recolectable->draw();
	}

	for (auto const& projectile : projectiles) {
		projectile->draw();
	}
	player->draw();

	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	

	backgroundPoints->draw();
	textPoints->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}
