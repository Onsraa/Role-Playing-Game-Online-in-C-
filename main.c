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
    pWindow = SDL_CreateWindow("Hello World !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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
            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

            // Chargement de la police
            TTF_Font *pFont = NULL;
            pFont = TTF_OpenFont("/home/gil/Bureau/dev/FreeSerifItalic.ttf", 24);

            // Vérification du chargement de la police
            if(pFont)
            {
                // Création de la surface contenant le texte
                SDL_Color color = { 0, 0, 255, 0 };
                SDL_Surface *pTextSurface = TTF_RenderText_Solid(pFont, "Welcome to RPG game", color);

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

                        // Rendu du fond noir
                        SDL_RenderClear(pRenderer);

                        // Rendu du texte
                        SDL_RenderCopy(pRenderer, pTextTexture, NULL, &textRect);

                        // Mise à jour du rendu
                        SDL_RenderPresent(pRenderer);

                        // Attente de l'appui d'une touche
                        SDL_Event e;
                        while(1){
                            if(SDL_PollEvent(&e)){
                                if(e.type == SDL_QUIT || e.key.keysym.sym==SDLK_ESCAPE){
                                    break;
                                }
                            }
                        }

                        // Destruction de la texture
                        SDL_DestroyTexture(pTextTexture);
                    }
                    else
                    {
                        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
                    }

                    // Destruction de la surface
                    SDL_FreeSurface(pTextSurface);
                }
                else
                {
                    printf("Erreur lors de la création de la surface : %s\n", TTF_GetError());
                }

                // Fermeture de la police
                TTF_CloseFont(pFont);
            }
            else
            {
                printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
            }

            // Destruction du contexte renderer
            SDL_DestroyRenderer(pRenderer);
        }
        else
        {
            printf("Erreur lors de la création du contexte renderer : %s\n", SDL_GetError());
        }

        // Destruction de la fenêtre
        SDL_DestroyWindow(pWindow);
    }
    else
    {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
    }

    // Arrêt de la SDL
    SDL_Quit();
    TTF_Quit();

    return 0;
}