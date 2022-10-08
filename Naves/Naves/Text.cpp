#include "Text.h"

#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>

Text::Text(string content, float x, float y, Game* game) {
	this->content = content;
	this->x = x;
	this->y = y;
	this->game = game;
}

/*
void Text::draw() {
	SDL_Color color {255, 255, 255, 255};

	SDL_Surface* surface = TTF_RenderText_Blended(game->font, content.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	SDL_Rect rect{ x - surface->w / 2, y - surface->h / 2, surface->w, surface->h };

	SDL_FreeSurface(surface);
	SDL_RenderCopy(game->renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}
*/

void Text::draw() {
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255; //transparente

	SDL_Surface* surface = TTF_RenderText_Blended(game->font, content.c_str(), color);
	// c_str() transforma el string a cost *char;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	SDL_Rect rect; // Base de coordenadas esquina superior izquierda
	rect.x = x - surface->w / 2;
	rect.y = y - surface->h / 2;
	rect.w = surface->w;
	rect.h = surface->h;

	SDL_FreeSurface(surface);
	SDL_RenderCopy(game->renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}
