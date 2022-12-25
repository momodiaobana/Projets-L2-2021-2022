#include "headers.h"

// Destruction de la fen�tre en cas d'erreur de chargement
void destruction(char* errorMessage, SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Log("%s > ", errorMessage);
	SDL_Log("%s\n", SDL_GetError());
	exit(EXIT_FAILURE);
}

// Destruction de la fen�tre en cas d'erreur de chargement de l'image
void checkLoadedImg(SDL_Surface* img, char* errorMessage, SDL_Window* window, SDL_Renderer* renderer)
{
	if (img == NULL)
		destruction(errorMessage, window, renderer);
}

// Destruction de la fen�tre en cas d'erreur de chargement de la texture
void checkTexture(SDL_Texture* texture, char* errorMessage, SDL_Window* window, SDL_Renderer* renderer)
{
	if (texture == NULL)
		destruction(errorMessage, window, renderer);
}


//Affichage des r�gles du jeu 
void reglesDuJeu(SDL_Window* window, SDL_Renderer* renderer)
{
	// D�claration et initialisation des surfaces et textures
	SDL_Surface* menu = NULL;
	SDL_Texture* textureMenu = NULL;
	SDL_Surface* title = NULL, * lesRegles1 = NULL, * lesRegles2 = NULL, * lesRegles3 = NULL, * back = NULL;
	SDL_Texture* textureTitle = NULL, * textureRegles1 = NULL, * textureRegles2 = NULL, * textureRegles3 = NULL, * textureBack = NULL;
	SDL_Color colorTitle = { 238, 28, 36 }, texteColor = { 0, 0, 0 }, colorBack = { 255, 255, 255 };

	//D�claration des polices 
	TTF_Font* fontTitle, * fontTexte;

	// chargement des images
	menu = SDL_LoadBMP("images/ciel.bmp");
	checkLoadedImg(menu, "Erreur : Fond d'ecran", window, renderer);

	textureMenu = SDL_CreateTextureFromSurface(renderer, menu);
	checkTexture(textureMenu, "Erreur : Creation texture", window, renderer);


	SDL_Rect rectMenu = { "" };

	if (SDL_QueryTexture(textureMenu, NULL, NULL, &rectMenu.w, &rectMenu.h) != 0)
		destruction("Erreur : Creation texture", window, renderer);

	rectMenu.x = (WINDOW_WIDTH - rectMenu.w) / 2;
	rectMenu.y = (WINDOW_HEIGHT - rectMenu.h) / 2;



	if ((SDL_RenderCopy(renderer, textureMenu, NULL, &rectMenu) != 0))
		destruction("Erreur : Affichage texture", window, renderer);

	if (TTF_Init() == -1)
	{
		printf("Erreur d'initialisation de la TTF");
	}

	//Choix de la police 
	fontTitle = TTF_OpenFont("BRITANIC.ttf", 35);
	fontTexte = TTF_OpenFont("BRITANIC.ttf", 20);
	if (fontTitle == NULL || fontTexte == NULL)
		printf("Erreur de chargement de la police");

	// Ecriture des r�gles dans les surfaces
	title = TTF_RenderText_Blended(fontTitle, "Bienvenu dans DODGE BIRD", colorTitle);
	lesRegles1 = TTF_RenderText_Blended(fontTexte, "Ce jeu poss�de deux modes : le mode IA et le mode NORMAL GAME", texteColor);
	lesRegles2 = TTF_RenderText_Blended(fontTexte, "-En mode NORMAL GAME, vous devrez �viter les oiseaux gr�ce aux fl�ches directionnelles du clavier", texteColor);
	lesRegles3 = TTF_RenderText_Blended(fontTexte, "-En mode IA, vous pouvez regarder une simulation du jeu", texteColor);
	back = TTF_RenderText_Blended(fontTexte, "Appuyer sur �chap pour revenir en arri�re", colorBack);

	if (title == NULL || lesRegles1 == NULL || lesRegles2 == NULL || lesRegles3 == NULL || back == NULL)
		printf("Erreur de chargement du text");
	SDL_Rect positionTitle = { "" }, positionRegles1 = { "0","0","0","0" }, positionRegles2 = { "0","0","0","0" }, positionRegles3 = { "0","0","0","0" }, positionBack = { "0","0","0","0" };
	//Cr�ation des textures
	textureTitle = SDL_CreateTextureFromSurface(renderer, title);
	textureRegles1 = SDL_CreateTextureFromSurface(renderer, lesRegles1);
	textureRegles2 = SDL_CreateTextureFromSurface(renderer, lesRegles2);
	textureRegles3 = SDL_CreateTextureFromSurface(renderer, lesRegles3);
	textureBack = SDL_CreateTextureFromSurface(renderer, back);

	//Positions 
	positionTitle.x = 50;
	positionTitle.y = 150;
	positionTitle.w = title->w;
	positionTitle.h = title->h;

	positionRegles1.x = 50;
	positionRegles1.y = 200;
	positionRegles1.w = lesRegles1->w;
	positionRegles1.h = lesRegles1->h;

	positionRegles2.x = 50;
	positionRegles2.y = 250;
	positionRegles2.w = lesRegles2->w;
	positionRegles2.h = lesRegles2->h;

	positionRegles3.x = 50;
	positionRegles3.y = 300;
	positionRegles3.w = lesRegles3->w;
	positionRegles3.h = lesRegles3->h;

	positionBack.x = 400;
	positionBack.y = 400;
	positionBack.w = back->w;
	positionBack.h = back->h;

	SDL_bool runing = SDL_TRUE;
	SDL_Event event;

	//Boucle infinie permettant le maintien de la fen�tre
	while (runing)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			runing = SDL_FALSE;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return;
				break;
			default:
				break;

			}
		default:
			break;
		}

		//Affichage 
		SDL_RenderCopy(renderer, textureMenu, NULL, &rectMenu);
		SDL_RenderCopy(renderer, textureTitle, NULL, &positionTitle);
		SDL_RenderCopy(renderer, textureRegles1, NULL, &positionRegles1);
		SDL_RenderCopy(renderer, textureRegles2, NULL, &positionRegles2);
		SDL_RenderCopy(renderer, textureRegles3, NULL, &positionRegles3);
		SDL_RenderCopy(renderer, textureBack, NULL, &positionBack);
		SDL_RenderPresent(renderer);
	}

	//lib�ration des espaces allou�s et fermeture de la fen�tre
	TTF_CloseFont(fontTitle);
	TTF_CloseFont(fontTexte);
	TTF_Quit();

	SDL_FreeSurface(title);
	SDL_FreeSurface(lesRegles1);
	SDL_FreeSurface(lesRegles2);
	SDL_FreeSurface(lesRegles3);

	SDL_DestroyTexture(textureMenu);
	SDL_DestroyTexture(textureRegles1);
	SDL_DestroyTexture(textureRegles2);
	SDL_DestroyTexture(textureRegles3);
	SDL_DestroyTexture(textureBack);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}



//Fonction de mise en pause du jeu : A am�liorer
void pause(SDL_Window* window, SDL_Renderer* renderer, Mix_Music* music)
{
	SDL_Surface* menu = NULL;
	SDL_Texture* textureMenu = NULL;
	SDL_Surface* play, * quit, * regles, * title;
	SDL_Texture* texturePlay = NULL, * textureQuit = NULL, * textureRegles, * textureTitle = NULL;
	SDL_Color texteColor = { 0, 0, 0 }, colorTitle = { 255, 255, 255 };

	TTF_Font* fontTexte, * fontTitle;

	menu = SDL_LoadBMP("images/ciel.bmp");
	checkLoadedImg(menu, "Erreur : Fond d'ecran", window, renderer);

	textureMenu = SDL_CreateTextureFromSurface(renderer, menu);
	SDL_FreeSurface;
	checkTexture(textureMenu, "Erreur : Creation texture", window, renderer);

	SDL_Rect rectMenu = { "" };

	if (SDL_QueryTexture(textureMenu, NULL, NULL, &rectMenu.w, &rectMenu.h) != 0)
		destruction("Erreur : Creation texture", window, renderer);

	rectMenu.x = (WINDOW_WIDTH - rectMenu.w) / 2;
	rectMenu.y = (WINDOW_HEIGHT - rectMenu.h) / 2;

	if ((SDL_RenderCopy(renderer, textureMenu, NULL, &rectMenu) != 0))
		destruction("Erreur : Affichage texture", window, renderer);

	if (TTF_Init() == -1)
	{
		printf("Erreur d'initialisation de la TTF");
	}

	fontTexte = TTF_OpenFont("BRITANIC.ttf", 50);
	fontTitle = TTF_OpenFont("BRITANIC.ttf", 70);
	if (fontTexte == NULL || fontTitle == NULL)
		printf("Erreur de chargement de la police");

	play = TTF_RenderText_Blended(fontTexte, "P-Play", texteColor);
	quit = TTF_RenderText_Blended(fontTexte, "Q-Quit", texteColor);
	regles = TTF_RenderText_Blended(fontTexte, "R-R�gles", texteColor);
	title = TTF_RenderText_Blended(fontTitle, "PAUSE", colorTitle);

	if (title == NULL || play == NULL || quit == NULL || regles == NULL)
		printf("Erreur de chargement du text");

	SDL_Rect positionPlay = { "" }, positionQuit = { "" }, positionRegles = { "" }, positionTitle = { "" };

	textureTitle = SDL_CreateTextureFromSurface(renderer, title);
	texturePlay = SDL_CreateTextureFromSurface(renderer, play);
	textureQuit = SDL_CreateTextureFromSurface(renderer, quit);
	textureRegles = SDL_CreateTextureFromSurface(renderer, regles);


	positionTitle.x = 750;
	positionTitle.y = 400;
	positionTitle.w = title->w;
	positionTitle.h = title->h;

	positionPlay.x = 400;
	positionPlay.y = 200;
	positionPlay.w = play->w;
	positionPlay.h = play->h;

	positionRegles.x = positionPlay.x;
	positionRegles.y = positionPlay.y + 50;
	positionRegles.w = regles->w;
	positionRegles.h = regles->h;

	positionQuit.x = positionPlay.x;
	positionQuit.y = positionPlay.y + 100;
	positionQuit.w = quit->w;
	positionQuit.h = quit->h;



	SDL_bool runing = SDL_TRUE;
	SDL_Event event;

	while (runing)
	{
		//Mise en pause du son des oiseaux
		Mix_PauseMusic();

		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			runing = SDL_FALSE;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_p:
				Mix_PlayMusic(music, -1);
				inGame(window, renderer, music);
				break;
			case SDLK_r:
				reglesDuJeu(window, renderer);
				break;
			case SDLK_q:
				TTF_CloseFont(fontTexte);
				TTF_Quit();

				SDL_FreeSurface(play);
				SDL_FreeSurface(title);
				SDL_FreeSurface(regles);
				SDL_FreeSurface(quit);


				SDL_DestroyTexture(textureMenu);
				SDL_DestroyTexture(textureTitle);
				SDL_DestroyTexture(texturePlay);
				SDL_DestroyTexture(textureRegles);
				SDL_DestroyTexture(textureQuit);;

				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);

				SDL_Quit();
				break;



			default:
				break;

			}
		default:
			break;
		}
		SDL_RenderCopy(renderer, textureMenu, NULL, &rectMenu);
		SDL_RenderCopy(renderer, textureTitle, NULL, &positionTitle);
		SDL_RenderCopy(renderer, texturePlay, NULL, &positionPlay);
		SDL_RenderCopy(renderer, textureRegles, NULL, &positionRegles);
		SDL_RenderCopy(renderer, textureQuit, NULL, &positionQuit);
		SDL_RenderPresent(renderer);
	}

	TTF_CloseFont(fontTexte);
	TTF_Quit();

	SDL_FreeSurface(play);
	SDL_FreeSurface(title);
	SDL_FreeSurface(regles);
	SDL_FreeSurface(quit);


	SDL_DestroyTexture(textureMenu);
	SDL_DestroyTexture(textureTitle);
	SDL_DestroyTexture(texturePlay);
	SDL_DestroyTexture(textureRegles);
	SDL_DestroyTexture(textureQuit);;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}



// Affichage du game over  : fin de partie
void gameOver(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_Surface* menu = NULL, * gameOver = NULL, * back = NULL;
	SDL_Texture* textureMenu = NULL, * textureGameOver = NULL, * textureBack;

	SDL_Color  colorBack = { 255, 255, 255 };

	TTF_Font* fontBack;

	menu = SDL_LoadBMP("images/ciel.bmp");
	checkLoadedImg(menu, "Erreur : Fond d'ecran", window, renderer);

	textureMenu = SDL_CreateTextureFromSurface(renderer, menu);
	SDL_FreeSurface;
	checkTexture(textureMenu, "Erreur : Creation texture", window, renderer);

	SDL_Rect rectMenu = { "" };

	if (SDL_QueryTexture(textureMenu, NULL, NULL, &rectMenu.w, &rectMenu.h) != 0)
		destruction("Erreur : Creation texture", window, renderer);

	rectMenu.x = (WINDOW_WIDTH - rectMenu.w) / 2;
	rectMenu.y = (WINDOW_HEIGHT - rectMenu.h) / 2;

	if ((SDL_RenderCopy(renderer, textureMenu, NULL, &rectMenu) != 0))
		destruction("Erreur : Affichage texture", window, renderer);

	gameOver = SDL_LoadBMP("images/gameOver.bmp");
	checkLoadedImg(gameOver, "Erreur : Fond d'ecran", window, renderer);

	textureGameOver = SDL_CreateTextureFromSurface(renderer, gameOver);

	SDL_FreeSurface;
	checkTexture(textureGameOver, "Erreur : Creation texture", window, renderer);

	SDL_Rect positionGameOver = { "" }, positionBack = { "" };

	if (SDL_QueryTexture(textureGameOver, NULL, NULL, &positionGameOver.w, &positionGameOver.h) != 0)
		destruction("Erreur : Creation texture", window, renderer);

	if ((SDL_RenderCopy(renderer, textureGameOver, NULL, &positionGameOver) != 0))
		destruction("Erreur : Affichage texture", window, renderer);




	positionGameOver.x = WINDOW_WIDTH / 4;
	positionGameOver.y = 20;
	positionGameOver.w = gameOver->w;
	positionGameOver.h = gameOver->w;



	if (TTF_Init() == -1)
	{
		printf("Erreur d'initialisation de la TTF");
	}

	fontBack = TTF_OpenFont("BRITANIC.ttf", 20);
	if (fontBack == NULL)
		printf("Erreur de chargement de la police");

	back = TTF_RenderText_Blended(fontBack, "Appuyer sur espace pour revenir au Menu", colorBack);

	if (back == NULL)
		printf("Erreur de chargement du text");


	positionBack.x = 30;
	positionBack.y = 30;
	positionBack.w = back->w;
	positionBack.h = back->h;

	textureBack = SDL_CreateTextureFromSurface(renderer, back);

	if (SDL_QueryTexture(textureBack, NULL, NULL, &positionBack.w, &positionBack.h) != 0)
		destruction("Erreur : Creation texture", window, renderer);

	if ((SDL_RenderCopy(renderer, textureBack, NULL, &positionBack) != 0))
		destruction("Erreur : Affichage texture", window, renderer);



	SDL_bool runing = SDL_TRUE;
	SDL_Event event;

	while (runing)
	{
		// Mise en pause du son de l'avion 
		Mix_PauseMusic();
		//Affichage du game over
		SDL_RenderCopy(renderer, textureMenu, NULL, &rectMenu);
		SDL_RenderCopy(renderer, textureGameOver, NULL, &positionGameOver);
		SDL_RenderCopy(renderer, textureBack, NULL, &positionBack);
		SDL_RenderPresent(renderer);
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			runing = SDL_FALSE;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
				Menu(window, renderer);
			break;
		default:
			break;
		}
	}
	//Destruction des espaces alou�s et fermeture 
	TTF_CloseFont(fontBack);
	TTF_Quit();

	SDL_FreeSurface(gameOver);
	SDL_FreeSurface(back);

	SDL_DestroyTexture(textureMenu);
	SDL_DestroyTexture(textureBack);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


//cr�ation des oiseaux � l'aide de la structure
bird* createBird(bird* Oiseau, SDL_Window* window, SDL_Renderer* renderer)
{
	Oiseau = (bird*)malloc(sizeof(bird));
	Oiseau->rect.x = WINDOW_WIDTH / 1.09;

	//affectation al�atoire des positions des oiseaux sur la coordonn�e y 
	Oiseau->rect.y = (rand() % 6) * (WINDOW_HEIGHT / 6);
	Oiseau->rect.w = 75;
	Oiseau->rect.h = 75;
	Oiseau->imgBird = SDL_LoadBMP("images/oiseau.bmp");
	checkLoadedImg(Oiseau->imgBird, "erreur de chargement de l'image de l'oiseau", window, renderer);
	Oiseau->texture = SDL_CreateTextureFromSurface(renderer, Oiseau->imgBird);
	checkTexture(Oiseau->texture, "erreur de chargement de la texture de l'oiseau", window, renderer);
	return Oiseau;
}

