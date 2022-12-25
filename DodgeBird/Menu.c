#include "headers.h"


void Menu(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_bool debut = SDL_TRUE;
	SDL_bool runing = SDL_TRUE;

	// déclaration et initialisation des surfaces et textures
	SDL_Surface* menu = NULL, * icon = NULL;
	SDL_Texture* textureMenu = NULL, * textureIcon = NULL;
	SDL_Texture* textureCommencer = NULL, * textureQuitter = NULL, * textureRegles = NULL, * textureMode = NULL, * textureHamza = NULL, * textureMomo = NULL;
	SDL_Surface* commencer = NULL, * quitter = NULL, * regles = NULL, * mode = NULL, * hamza, * momo;

	//déclaration et initialisation des polices d'écriture
	TTF_Font* font, * fontName;

	SDL_Color textecolor = { 0, 0, 0 }, nameColor = { 255, 255, 255 };

	menu = SDL_LoadBMP("images/ciel.bmp");
	checkLoadedImg(menu, "Erreur : Fond d'ecran", window, renderer);

	textureMenu = SDL_CreateTextureFromSurface(renderer, menu);
	SDL_FreeSurface;
	checkTexture(textureMenu, "Erreur : Creation texture", window, renderer);

	icon = SDL_LoadBMP("images/oiseau.bmp");
	checkLoadedImg(icon, "Erreur : Fond d'ecran", window, renderer);

	textureIcon = SDL_CreateTextureFromSurface(renderer, icon);
	SDL_FreeSurface;
	checkTexture(textureIcon, "Erreur : Creation texture", window, renderer);

	SDL_Rect rectMenu;

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

	//Choix de la police d'écriture
	font = TTF_OpenFont("BRITANIC.ttf", 40);
	fontName = TTF_OpenFont("BRITANIC.ttf", 20);
	if (font == NULL || fontName)
		printf("Erreur de chargement de la police");

	//Ecriture dans les surfaces 
	commencer = TTF_RenderText_Blended(font, "1- NORMAL GAME", textecolor);
	mode = TTF_RenderText_Blended(font, "2- IA", textecolor);
	regles = TTF_RenderText_Blended(font, "3- REGLES", textecolor);
	quitter = TTF_RenderText_Blended(font, "4- QUITTER", textecolor);
	momo = TTF_RenderText_Blended(fontName, "MOUHAMED MOUNTAGA DIAO", nameColor);
	hamza = TTF_RenderText_Blended(fontName, "HAMZA DOUGAREM", nameColor);

	if (commencer == NULL || mode == NULL || regles == NULL || quitter == NULL || momo == NULL || hamza == NULL)
		printf("Erreur de chargement du/des text(s)");
	SDL_Rect positionCommencer, positionMode, positionRegles, positionQuitter, positionHamza, positionMomo;

	//Création des textures
	textureCommencer = SDL_CreateTextureFromSurface(renderer, commencer);
	textureMode = SDL_CreateTextureFromSurface(renderer, mode);
	textureRegles = SDL_CreateTextureFromSurface(renderer, regles);
	textureQuitter = SDL_CreateTextureFromSurface(renderer, quitter);
	textureHamza = SDL_CreateTextureFromSurface(renderer, hamza);
	textureMomo = SDL_CreateTextureFromSurface(renderer, momo);

	//Initialisation des positions
	positionCommencer.x = rectMenu.w / 3;
	positionCommencer.y = rectMenu.h / 2.7;
	positionCommencer.w = commencer->w;
	positionCommencer.h = commencer->h;

	positionMode.x = rectMenu.w / 3;
	positionMode.y = rectMenu.h / 2.2;
	positionMode.w = mode->w;
	positionMode.h = mode->h;

	positionRegles.x = rectMenu.w / 3;
	positionRegles.y = rectMenu.h / 1.9;
	positionRegles.w = regles->w;
	positionRegles.h = regles->h;

	positionQuitter.x = rectMenu.w / 3;
	positionQuitter.y = rectMenu.h / 1.7;
	positionQuitter.w = quitter->w;
	positionQuitter.h = quitter->h;

	positionHamza.x = 50;
	positionHamza.y = 50;
	positionHamza.w = hamza->w;
	positionHamza.h = hamza->h;

	positionMomo.x = 50;
	positionMomo.y = 70;
	positionMomo.w = momo->w;
	positionMomo.h = momo->h;

	//Initialisaton du son 
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return;

	if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
		SDL_Quit();
		return;
	}

	Mix_Music* music = Mix_LoadMUS("sons/biplane-flying-01.mp3");

	Mix_Music* chantOiseau = Mix_LoadMUS("sons/birds2.mp3");



	if (music == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
		Mix_CloseAudio();
		SDL_Quit();
		return;
	}


	SDL_Event event;
	//Boucle du menu 
	while (runing)
	{
		// image de l'icône et nom de la fenêtre 
		SDL_SetWindowTitle(window, "DODGE BIRD");
		SDL_SetWindowIcon(window, icon);
		//lancement de la musique du menu (chant des oiseaux)
		Mix_PlayMusic(chantOiseau, -1);

		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			runing = SDL_FALSE;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				//appuyer sur les touches numérique du clavier et non du pavé numérique
			case SDLK_1:
				//Lancement du mode NORMAL GAME et du son de l'avion
				Mix_PlayMusic(music, -1);
				inGame(window, renderer, music);
				break;

			case SDLK_2:
				//Lancement du mode IA et du son de l'avion
				Mix_PlayMusic(music, -1);
				IA(window, renderer, music);
				//printf("%d\n", now);
				
				break;

			case SDLK_3:
				reglesDuJeu(window, renderer);
				break;

			case SDLK_4:
				TTF_CloseFont(font);
				TTF_Quit();

				SDL_FreeSurface(commencer);
				SDL_FreeSurface(mode);
				SDL_FreeSurface(regles);
				SDL_FreeSurface(quitter);
				SDL_FreeSurface(hamza);
				SDL_FreeSurface(momo);
				SDL_Quit();
				exit(EXIT_FAILURE);


			}
		}


		//Affichage 

		SDL_RenderCopy(renderer, textureMenu, NULL, &rectMenu);

		SDL_RenderCopy(renderer, textureCommencer, NULL, &positionCommencer);
		SDL_RenderCopy(renderer, textureMode, NULL, &positionMode);
		SDL_RenderCopy(renderer, textureRegles, NULL, &positionRegles);
		SDL_RenderCopy(renderer, textureQuitter, NULL, &positionQuitter);
		SDL_RenderCopy(renderer, textureHamza, NULL, &positionHamza);
		SDL_RenderCopy(renderer, textureMomo, NULL, &positionMomo);
		SDL_RenderPresent(renderer);
	}

	//Fermeture et libération des espaces alloués
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_FreeSurface(commencer);
	SDL_FreeSurface(mode);
	SDL_FreeSurface(regles);
	SDL_FreeSurface(quitter);
	SDL_FreeSurface(hamza);
	SDL_FreeSurface(momo);

	Mix_FreeMusic(music);
	Mix_FreeMusic(chantOiseau);
	Mix_Quit;

	SDL_Quit();

}

















