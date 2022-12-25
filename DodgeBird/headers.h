#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef HEADERS_H
#define HEADERS_H

//------------- VARIABLES GLOBALES -------------
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 494

//------------ STRUCTURE -------------------------
typedef struct Obstacles
{
	SDL_Surface* imgBird;
	SDL_Rect rect;
	SDL_Texture* texture;
}bird;




//------------------ FONCTIONS -------------------

// fonctions permettant de sécurisation
void destruction(char* errorMessage, SDL_Window* window, SDL_Renderer* renderer);
void checkLoadedImg(SDL_Surface* img, char* errorMessage, SDL_Window* window, SDL_Renderer* renderer);
void checkTexture(SDL_Texture* texture, char* errorMessage, SDL_Window* window, SDL_Renderer* renderer);

void reglesDuJeu(SDL_Window* window, SDL_Renderer* renderer);

bird* createBird(bird* Oiseau, SDL_Window* window, SDL_Renderer* renderer);

// JEU 
void Menu(SDL_Window* window, SDL_Renderer* renderer);
void pause(SDL_Window* window, SDL_Renderer* renderer, Mix_Music* music);
void gameOver(SDL_Window* window, SDL_Renderer* renderer);
void inGame(SDL_Window* window, SDL_Renderer* renderer, Mix_Music* music);
void IA(SDL_Window* window, SDL_Renderer* renderer, Mix_Music* music);

#endif // !HEADERS_H
