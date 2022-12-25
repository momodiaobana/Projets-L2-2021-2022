#include "headers.h"


// Mode IA 
void IA(SDL_Window* window, SDL_Renderer* renderer, Mix_Music* music)
{
	unsigned int startinTime = SDL_GetTicks();
	// D�claration et initialisation des surfaces et textures
	SDL_Surface* menu = NULL;
	SDL_Texture* textureMenu = NULL;
	//chargement du background
	menu = SDL_LoadBMP("images/ciel.bmp");
	checkLoadedImg(menu, "Erreur : Fond d'ecran", window, renderer);

	textureMenu = SDL_CreateTextureFromSurface(renderer, menu);
	SDL_FreeSurface;
	checkTexture(textureMenu, "Erreur : Creation texture", window, renderer);

	//Position menu
	SDL_Rect rectMenu = { "" };

	if (SDL_QueryTexture(textureMenu, NULL, NULL, &rectMenu.w, &rectMenu.h) != 0)
		destruction("Erreur : Creation texture", window, renderer);

	rectMenu.x = (WINDOW_WIDTH - rectMenu.w) / 2;
	rectMenu.y = (WINDOW_HEIGHT - rectMenu.h) / 2;



	if ((SDL_RenderCopy(renderer, textureMenu, NULL, &rectMenu) != 0))
		destruction("Erreur : Affichage texture", window, renderer);

	//Chargment de l'avion
	SDL_Surface* loadPlane = NULL;
	SDL_Texture* plane = NULL;

	loadPlane = SDL_LoadBMP("images/avion.bmp");
	checkLoadedImg(loadPlane, "Erreur : chargement avion", window, renderer);

	plane = SDL_CreateTextureFromSurface(renderer, loadPlane);
	checkTexture(plane, "Erreur : Chargement avion", window, renderer);

	SDL_Rect rectPlane = { "" };
	if (SDL_QueryTexture(plane, NULL, NULL, &rectPlane.w, &rectPlane.h) != 0)
		destruction("Erreur : Creation texture plane", window, renderer);

	//param�tres de l'avion
	rectPlane.x = (WINDOW_WIDTH / 100);
	rectPlane.y = (WINDOW_HEIGHT / 6);
	rectPlane.w = (WINDOW_WIDTH / 6);
	rectPlane.h = (WINDOW_HEIGHT / 6);

	if (SDL_RenderCopy(renderer, plane, NULL, &rectPlane) != 0)
		destruction("Erreur : Affichage texture plane", window, renderer);

	// compteur et variables bool�enes
	SDL_bool program_actif = SDL_TRUE;
	SDL_bool generer = SDL_TRUE;
	int compt = 0;

	// D�claration et initialisation des oiseaux
	bird* obstacle1 = NULL;
	bird* obstacle2 = NULL;
	bird* obstacle3 = NULL;
	bird* obstacle4 = NULL;
	bird* obstacle5 = NULL;

	unsigned int time = 0;

	//Boucle infinie permettant le maintien de la fen�tre
	while (program_actif)
	{
		time = SDL_GetTicks();
		unsigned int delta_time = time - startinTime;
		printf("%d\n", delta_time);
		//Cr�ation des oiseaux
		obstacle1 = createBird(obstacle1, window, renderer);
		obstacle2 = createBird(obstacle2, window, renderer);
		obstacle3 = createBird(obstacle3, window, renderer);
		obstacle4 = createBird(obstacle4, window, renderer);
		obstacle5 = createBird(obstacle5, window, renderer);

		compt++;

		//Variables de gestion des �venements
		SDL_Event event;

		//gestion des �v�nements
		while (SDL_PollEvent(&event))
		{


			switch (event.type)
			{

				if (event.type == SDLK_c)
				{

			case SDL_KEYDOWN:

			case SDLK_ESCAPE:
				pause(window, renderer, music);
				break;

				}
				//Gestion fermeture fenetre
			case SDL_QUIT:
				program_actif = SDL_FALSE;

				break;

			default:
				break;
			}

		}

		//Automatisation du deplacement de l'avion

		if (compt % 50 == 0)
		{
			while (obstacle1->rect.x > -100)
			{
				//condition permettant d'�viter les oiseaux 
				if (rectPlane.y == obstacle1->rect.y || rectPlane.y == obstacle2->rect.y || rectPlane.y == obstacle3->rect.y || rectPlane.y == obstacle4->rect.y || rectPlane.y == obstacle5->rect.y)
				{
					if (rectPlane.y > 0 && rectPlane.y <= WINDOW_HEIGHT)
					{
						//deplacement de l'avion suivant la coordonn�e y 
						rectPlane.y += WINDOW_HEIGHT / 6;
					}

				}



				//Affichage du tout 
				SDL_RenderCopy(renderer, textureMenu, NULL, &rectMenu);
				SDL_RenderCopy(renderer, plane, NULL, &rectPlane);
				SDL_RenderCopy(renderer, obstacle1->texture, NULL, &obstacle1->rect);
				SDL_RenderCopy(renderer, obstacle2->texture, NULL, &obstacle2->rect);
				SDL_RenderCopy(renderer, obstacle3->texture, NULL, &obstacle3->rect);
				SDL_RenderCopy(renderer, obstacle4->texture, NULL, &obstacle4->rect);
				SDL_RenderCopy(renderer, obstacle5->texture, NULL, &obstacle5->rect);
				SDL_RenderPresent(renderer);

				//d�placement des oiseaux vers la gauche suivant la coordonn�e x 
				if (time < 10000)
					SDL_Delay(1);
				else if (time > 10000 && time < 20000)
					SDL_Delay(0.7);
				else
					SDL_Delay(0.5);
				obstacle1->rect.x--;
				obstacle2->rect.x--;
				obstacle3->rect.x--;
				obstacle4->rect.x--;
				obstacle5->rect.x--;
				//Gestion de la collision
				if ((obstacle1->rect.x >= rectPlane.x && obstacle1->rect.x <= rectPlane.x + rectPlane.w - 50) && (obstacle1->rect.y == rectPlane.y) || (obstacle2->rect.x >= rectPlane.x && obstacle2->rect.x <= rectPlane.x + rectPlane.w - 50) && (obstacle2->rect.y == rectPlane.y) || (obstacle3->rect.x >= rectPlane.x && obstacle3->rect.x <= rectPlane.x + rectPlane.w - 50) && (obstacle3->rect.y == rectPlane.y) || (obstacle4->rect.x >= rectPlane.x && obstacle4->rect.x <= rectPlane.x + rectPlane.w - 50) && (obstacle4->rect.y == rectPlane.y) || (obstacle5->rect.x >= rectPlane.x && obstacle5->rect.x <= rectPlane.x + rectPlane.w - 50) && (obstacle5->rect.y == rectPlane.y))
					gameOver(window, renderer);
			}
		}
		//replacement de l'avion � sa position de base 
		rectPlane.y = (WINDOW_HEIGHT / 6);

		//Lib�ration des espaces allou�s afin de pouvoir les r�allou�s pour de nouveaux oiseaux
		SDL_FreeSurface(obstacle1->imgBird);
		SDL_FreeSurface(obstacle2->imgBird);
		SDL_FreeSurface(obstacle3->imgBird);
		SDL_FreeSurface(obstacle4->imgBird);
		SDL_FreeSurface(obstacle5->imgBird);

		SDL_DestroyTexture(obstacle1->texture);
		SDL_DestroyTexture(obstacle2->texture);
		SDL_DestroyTexture(obstacle3->texture);
		SDL_DestroyTexture(obstacle4->texture);
		SDL_DestroyTexture(obstacle5->texture);

		free(obstacle1);
		free(obstacle2);
		free(obstacle3);
		free(obstacle4);
		free(obstacle5);

		obstacle1 = NULL;
		obstacle2 = NULL;
		obstacle3 = NULL;
		obstacle4 = NULL;
		obstacle5 = NULL;
	}


	//Lib�ration des espaces et fermeture de la fen�tre
	SDL_FreeSurface(menu);
	SDL_FreeSurface(loadPlane);
	SDL_FreeSurface(obstacle1->imgBird);
	SDL_FreeSurface(obstacle2->imgBird);
	SDL_FreeSurface(obstacle3->imgBird);
	SDL_FreeSurface(obstacle4->imgBird);
	SDL_FreeSurface(obstacle5->imgBird);

	SDL_DestroyTexture(textureMenu);
	SDL_DestroyTexture(plane);
	SDL_DestroyTexture(obstacle1->texture);
	SDL_DestroyTexture(obstacle2->texture);
	SDL_DestroyTexture(obstacle3->texture);
	SDL_DestroyTexture(obstacle4->texture);
	SDL_DestroyTexture(obstacle5->texture);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	free(obstacle1);
	free(obstacle2);
	free(obstacle3);
	free(obstacle4);
	free(obstacle5);

	obstacle1 = NULL;
	obstacle2 = NULL;
	obstacle3 = NULL;
	obstacle4 = NULL;
	obstacle5 = NULL;

	SDL_Quit();
}