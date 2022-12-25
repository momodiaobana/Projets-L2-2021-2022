#include "headers.h"

void createWindow()
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;


	//Initialisation SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Erreur : Initialisation de la SDL > %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	//Cr�ation fenetre + rendu

	if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer, SDL_WINDOW_RESIZABLE) != 0)
	{
		SDL_Log("Erreur : Cr�ation fen�tre > %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	//.................................//
	Menu(window, renderer);


	//Fermeture et suppresion de toutes les cr�ations
	SDL_DestroyTexture;
	SDL_DestroyRenderer;
	SDL_DestroyWindow(window);
	SDL_Quit();

}