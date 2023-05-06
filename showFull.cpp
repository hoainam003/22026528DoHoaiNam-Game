#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

#include "showFull.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void showMenu(SDL_Renderer* gRenderer, SDL_Texture* gStartMenu)
{
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    //show full table
    SDL_RenderCopy( gRenderer, gStartMenu, NULL, NULL );
    SDL_RenderPresent( gRenderer );
    SDL_Delay(500);
}

void showTable(SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy,
                   int* arr, int n)
{
    //code render

    // Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    //show full table
    SDL_RenderCopy( gRenderer, gTextureGalaxy, NULL, NULL );
    SDL_RenderPresent( gRenderer );
    SDL_Rect viewport;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            viewport.x = 140 + i*140;
            viewport.y = 40 + j*140;
            viewport.w = 100;
            viewport.h = 100;
            SDL_RenderSetViewport( gRenderer, &viewport );
            //Render texture to screen
            SDL_RenderCopy( gRenderer, gTextureBox, NULL, NULL );
        }
    }
    viewport.x = 0; viewport.y = 0; viewport.w = SCREEN_WIDTH; viewport.h = SCREEN_HEIGHT;
    SDL_RenderSetViewport( gRenderer, &viewport );
    //Update screen
    SDL_RenderPresent( gRenderer );
    SDL_Delay(300);

}

void showSwap(SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy,
                   int* arr, int n, int x, int y, int direction, int timewait)
{
    for (int k=0; k<8; k++) {
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //show full table
        SDL_RenderCopy( gRenderer, gTextureGalaxy, NULL, NULL );
        SDL_RenderPresent( gRenderer );
        SDL_Rect viewport;
        if (direction == 1){
            for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                    if (i == y && j == x) {
                        viewport.x = 140 + j*140 + k*20; viewport.y = 40 + i*140; viewport.w = 100; viewport.h = 100;
                        SDL_RenderSetViewport( gRenderer, &viewport );
                        SDL_RenderCopy( gRenderer, gTextureBox, NULL, NULL );
                        j++;
                        viewport.x = 140 + j*140 - k*20; viewport.y = 40 + i*140; viewport.w = 100; viewport.h = 100;
                        SDL_RenderSetViewport( gRenderer, &viewport );
                        SDL_RenderCopy( gRenderer, gTextureBox, NULL, NULL );
                    } else {
                        viewport.x = 140 + j*140;
                        viewport.y = 40 + i*140;
                        viewport.w = 100;
                        viewport.h = 100;
                        SDL_RenderSetViewport( gRenderer, &viewport );
                        SDL_RenderCopy( gRenderer, gTextureBox, NULL, NULL );
                    }
                }
            }
        } else if (direction == 2){
            for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                    if (i == y && j == x) {
                        viewport.x = 140 + j*140; viewport.y = 40 + i*140 + k*20; viewport.w = 100; viewport.h = 100;
                        SDL_RenderSetViewport( gRenderer, &viewport );
                        SDL_RenderCopy( gRenderer, gTextureBox, NULL, NULL );
                    } else if (i == y + 1 && j == x) {
                        viewport.x = 140 + j*140; viewport.y = 40 + i*140 - k*20; viewport.w = 100; viewport.h = 100;
                        SDL_RenderSetViewport( gRenderer, &viewport );
                        SDL_RenderCopy( gRenderer, gTextureBox, NULL, NULL );
                    } else {
                        viewport.x = 140 + j*140;
                        viewport.y = 40 + i*140;
                        viewport.w = 100;
                        viewport.h = 100;
                        SDL_RenderSetViewport( gRenderer, &viewport );
                        SDL_RenderCopy( gRenderer, gTextureBox, NULL, NULL );
                    }
                }
            }
        }
        viewport.x = 0; viewport.y = 0; viewport.w = SCREEN_WIDTH; viewport.h = SCREEN_HEIGHT;
        SDL_RenderSetViewport( gRenderer, &viewport );
        //Update screen
        SDL_RenderPresent( gRenderer );
        SDL_Delay(timewait);
        }
    SDL_Delay(timewait*10);
}

void showBombTable(SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy, SDL_Texture* gTextureMar,
                   int* arr, int n, int *locatBombX, int *locatBombY, int bomb)
{
    //code render

    // Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    //show full table
    SDL_RenderCopy( gRenderer, gTextureGalaxy, NULL, NULL );
    SDL_RenderPresent( gRenderer );
    SDL_Rect viewport;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            viewport.x = 140 + i*140;
            viewport.y = 40 + j*140;
            viewport.w = 100;
            viewport.h = 100;
            SDL_RenderSetViewport( gRenderer, &viewport );
            if ( (j == *(locatBombX + 0) && i == *(locatBombY + 0)) || (j == *(locatBombX + 1) && i == *(locatBombY + 1)) ) {
                    SDL_RenderCopy( gRenderer, gTextureMar, NULL, NULL );
            }
            //Render texture to screen
             else SDL_RenderCopy( gRenderer, gTextureBox, NULL, NULL );
        }
    }
    viewport.x = 0; viewport.y = 0; viewport.w = SCREEN_WIDTH; viewport.h = SCREEN_HEIGHT;
    SDL_RenderSetViewport( gRenderer, &viewport );
    //Update screen
    SDL_RenderPresent( gRenderer );
    SDL_Delay(1000);

}

void showResult(SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy, SDL_Texture* gTextureMar, SDL_Texture* gTextureLevelup,
                   int* arr, int n, int *locatBombX, int *locatBombY, int bomb, int result, int tmp, int timewait)
{

    const int levelupw = 600;
    const int leveluph = 600;

    if (result == 1) {
        //code render

        // Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //show full table
        SDL_RenderCopy( gRenderer, gTextureGalaxy, NULL, NULL );
        SDL_RenderPresent( gRenderer );
        SDL_Rect viewport;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                viewport.x = 140 + i*140;
                viewport.y = 40 + j*140;
                viewport.w = 100;
                viewport.h = 100;
                SDL_RenderSetViewport( gRenderer, &viewport );
                if ( (j == *(locatBombX + tmp) && i == *(locatBombY + tmp)) ) {
                        SDL_RenderCopy( gRenderer, gTextureMar, NULL, NULL );
                }
                //Render texture to screen
                else SDL_RenderCopy( gRenderer, gTextureBox, NULL, NULL );
            }
        }
        viewport.x = 0; viewport.y = 0; viewport.w = SCREEN_WIDTH; viewport.h = SCREEN_HEIGHT;
        SDL_RenderSetViewport( gRenderer, &viewport );
        //Update screen
        SDL_RenderPresent( gRenderer );
        SDL_Delay(500);
    } else if (result == 2) {
        showBombTable(gRenderer, gTextureBox, gTextureGalaxy, gTextureMar, arr, n, locatBombX, locatBombY, bomb);
        if (timewait >= 20) {
            for (int i=0; i<10; i++) {
                SDL_Rect viewport;
                viewport.x = (SCREEN_WIDTH - levelupw/(10 - i)) / 2;
                viewport.y = (SCREEN_HEIGHT - leveluph/(10 - i)) / 2;
                viewport.w = levelupw/(10 - i);
                viewport.h = leveluph/(10 - i);
                SDL_RenderSetViewport( gRenderer, &viewport );
                SDL_RenderCopy( gRenderer, gTextureLevelup, NULL, NULL );
                viewport.x = 0; viewport.y = 0; viewport.w = SCREEN_WIDTH; viewport.h = SCREEN_HEIGHT;
                SDL_RenderSetViewport( gRenderer, &viewport );
                SDL_RenderPresent( gRenderer );
                SDL_Delay(50);
            }
        } SDL_Delay(1000);
    }
}

void showWinner(SDL_Renderer* gRenderer, SDL_Texture* gTextureCongrats)
{
    const int startw = 800;
    const int starth = 600;
    for (int i=0; i<10; i++) {
        SDL_Rect viewport;
        viewport.x = (SCREEN_WIDTH - startw/(10 - i)) / 2;
        viewport.y = (SCREEN_HEIGHT - starth/(10 - i)) / 2;
        viewport.w = startw/(10 - i);
        viewport.h = starth/(10 - i);
        SDL_RenderSetViewport( gRenderer, &viewport );
        SDL_RenderCopy( gRenderer, gTextureCongrats, NULL, NULL );
        viewport.x = 0; viewport.y = 0; viewport.w = SCREEN_WIDTH; viewport.h = SCREEN_HEIGHT;
        SDL_RenderSetViewport( gRenderer, &viewport );
        SDL_RenderPresent( gRenderer );
        SDL_Delay(50);
    }

}
