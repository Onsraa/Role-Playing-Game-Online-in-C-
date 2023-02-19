#include <SDL2/SDL.h> //Inclut les fonctionnalites de la SDL
#include <SDL2/SDL_ttf.h> //Inclut les fonctionnalites pour afficher du texte
#include <stdio.h>

// Taille de la fenêtre
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }

    // Initialisation du TTF
    if(TTF_Init() != 0)
    {
        printf("Erreur lors de l'initialisation du TTF : %s\n", TTF_GetError());
        return -1;
    }

    // Création de la fenêtre
    SDL_Window *pWindow = NULL;
    pWindow = SDL_CreateWindow("Donjon Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Vérification de la création de la fenêtre
    if(pWindow)
    {
        // Création du contexte renderer
        SDL_Renderer *pRenderer = NULL;
        pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

        // Vérification de la création du contexte renderer
        if(pRenderer)
        {
            // Définition de la couleur de fond
            SDL_SetRenderDrawColor(pRenderer, 0, 0, 25, 255);

            // Chargement de la police
            TTF_Font *pFont = NULL;
            pFont = TTF_OpenFont("/home/gil/Bureau/dev/FreeSerifItalic.ttf", 24);

            // Vérification du chargement de la police
            if(pFont)
            {
                // Création de la surface contenant le texte
                SDL_Color color = { 0, 0, 255, 0 };
                SDL_Surface *pTextSurface = TTF_RenderText_Solid(pFont, "Welcome to Donjon Games", color);

                // Vérification de la création de la surface
                if(pTextSurface)
                {
                    // Création de la texture à partir de la surface
                    SDL_Texture *pTextTexture = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);

                    // Vérification de la création de la texture
                    if(pTextTexture)
                    {
                        // Définition des dimensions de la texture
                        SDL_Rect textRect;
                        textRect.x = (WINDOW_WIDTH - pTextSurface->w) / 2;
                        textRect.y = (WINDOW_HEIGHT - pTextSurface->h) / 2;
                        textRect.w = pTextSurface->w;
                        textRect.h = pTextSurface->h;

                        // Position initiale de la texture
                        int x = textRect.x;

                        // Boucle de jeu infinie
                        while(1)
                        {
                            // Gestion des évènements
                            SDL_Event event;
                            if(SDL_PollEvent(&event)){
                                if(event.type == SDL_QUIT || event.key.keysym.sym==SDLK_ESCAPE){
                                    SDL_DestroyTexture(pTextTexture);
                                    SDL_FreeSurface(pTextSurface);
                                    TTF_CloseFont(pFont);
                                    SDL_DestroyRenderer(pRenderer);
                                    SDL_DestroyWindow(pWindow);
                                    SDL_Quit();
                                    break;
                                }
                            }

                            // Rafraîchissement de l'écran
                            SDL_RenderClear(pRenderer);

                            // Met à jour la position de la texture
                            textRect.x = x;
                            x += 10;

                            // Affichage de la texture
                            SDL_RenderCopy(pRenderer, pTextTexture, NULL, &textRect);

                            // Mise à jour de l'écran
                            SDL_RenderPresent(pRenderer);

                            // Pause
                            SDL_Delay(160);
                        }
                    }

                    // Destruction de la texture
                    SDL_DestroyTexture(pTextTexture);
                }

                // Destruction de la surface
                SDL_FreeSurface(pTextSurface);
            }

            // Fermeture de la police
            TTF_CloseFont(pFont);
        }

        // Destruction du contexte renderer
        SDL_DestroyRenderer(pRenderer);
    }

    // Destruction de la fenêtre
    SDL_DestroyWindow(pWindow);

    // Fermeture de la SDL
    SDL_Quit();

    return 0;
}