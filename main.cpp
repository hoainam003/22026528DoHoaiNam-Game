
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <windows.h>

#include "showFull.h"
#include "generate.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int n = 4;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gStartMenu = NULL;
SDL_Texture* gTextureBox = NULL;
SDL_Texture* gTextureMar = NULL;
SDL_Texture* gTextureGalaxy = NULL;
SDL_Texture* gTextureCongrats = NULL;
SDL_Texture* gTextureLevelup = NULL;
SDL_Texture* gTextureGameOver = NULL;
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gGameOver = NULL;
Mix_Chunk *gWinner = NULL;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Finding ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}

bool loadMedia()
{

	//Loading success flag
	bool success = true;

    gScratch = Mix_LoadWAV( "Monkeys.mp3" );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gGameOver = Mix_LoadWAV( "Game Over Sound Effect.mp3" );
    if( gGameOver == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gWinner = Mix_LoadWAV( "Winner Sound Effect.mp3" );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

	//Load texture
	gStartMenu = loadTexture( "Backgroundmenu.png" );
	if( gStartMenu == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}
	gTextureBox = loadTexture( "Cup.png" );
	if( gTextureBox == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}
	gTextureMar = loadTexture( "Ball.png" );
	if( gTextureMar == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}
	gTextureGalaxy = loadTexture( "Background.jpg" );
	if( gTextureGalaxy == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}
	gTextureCongrats = loadTexture( "Winner.jpg" );
	if( gTextureCongrats == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}
	gTextureLevelup = loadTexture( "LevelUp.png" );
	if( gTextureLevelup == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}
	gTextureGameOver = loadTexture( "Gameover.jpg" );
	if( gTextureGameOver == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	//Nothing to load
	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture( gStartMenu );
	gStartMenu = NULL;
	SDL_DestroyTexture( gTextureBox );
	gTextureBox = NULL;
	SDL_DestroyTexture( gTextureMar );
	gTextureMar = NULL;
	SDL_DestroyTexture( gTextureGalaxy );
	gTextureGalaxy = NULL;
	SDL_DestroyTexture( gTextureCongrats );
	gTextureCongrats = NULL;
	SDL_DestroyTexture( gTextureGameOver );
	gTextureGameOver = NULL;

	Mix_FreeChunk( gScratch );
	gScratch = NULL;
	Mix_FreeChunk( gGameOver );
	gGameOver = NULL;
	Mix_FreeChunk( gWinner );
	gWinner = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

int main( int argc, char* args[] )
{

    const int numberOfBomb = 2;
    int bombLocatX[numberOfBomb], bombLocatY[numberOfBomb];
    int* table = generateTable(n, numberOfBomb, bombLocatX, bombLocatY);
    int tmp = 2;

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;
			int result = 0, oldresult = result;
			bool gameover = false;
			bool startGame = false;
            int timewait = 40;



			//Event handler
			SDL_Event e;

			while (startGame == false) {
                showMenu(gRenderer, gStartMenu);
                while( SDL_PollEvent( &e ) != 0 ) {
                    switch (e.type)
                    {
                    case SDL_QUIT:
                    {
                        startGame = true;
                        quit = true;
                        gameover = true;
                        break;
                    }

                    //Mouse button pressed
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        if (e.button.button == SDL_BUTTON_LEFT)
                        {
                            if (e.motion.x > 160 && e.motion.x < 365 && e.motion.y > 370 && e.motion.y < 500){
                                startGame = true;
                            }
                            if (e.motion.x > 423 && e.motion.x < 545 && e.motion.y > 370 && e.motion.y < 500){
                                startGame = true;
                                gameover = true;
                            }
                        }
                        break;
                    }
                    }
                }
			}

            Mix_PlayChannel( -1, gScratch,  100);
            while(gameover != true) {

                table = generateTable(n, numberOfBomb, bombLocatX, bombLocatY);
                showBombTable(gRenderer, gTextureBox, gTextureGalaxy, gTextureMar, table, n, bombLocatX, bombLocatY, numberOfBomb);
                showTable(gRenderer, gTextureBox, gTextureGalaxy, table, n);


                switchBomb(table, n, bombLocatX, bombLocatY, numberOfBomb,
                    gRenderer, gTextureBox, gTextureGalaxy, timewait);
                timewait -= 4;


                for (int i=0; i<numberOfBomb; i++) {
                printf( "bomb locat: %i and %i\n", *(bombLocatX + i), *(bombLocatY + i) );
                }

                while( !quit )
                {
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        switch (e.type)
                        {
                        case SDL_QUIT:
                        {
                            quit = true;
                            gameover = true;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN:
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                oldresult = result;
                                for (int l=0; l<numberOfBomb; l++) {
                                    int a = *(bombLocatX + l), b = *(bombLocatY + l);

                                    if (e.motion.x > 140 + b*140 && e.motion.x < 240 + b*140 && e.motion.y > 40 + a*140 && e.motion.y < 140 + a*140){
                                        result += 1;
                                        tmp = l;
                                    }
                                }
                                if (result > oldresult) {
                                     printf("Correct\n");
                                     printf("result %i\n time %i\n", result, timewait);

                                     if (timewait < 20 && result == 2) {
                                        showResult(gRenderer, gTextureBox, gTextureGalaxy, gTextureMar, gTextureLevelup, table, n, bombLocatX, bombLocatY, numberOfBomb, result, tmp, timewait);
                                        Mix_HaltChannel(-1);
                                        Mix_PlayChannel( -1, gWinner,  0);
                                        showWinner(gRenderer, gTextureCongrats);
                                        Sleep(5000);
                                        gameover = true; quit = true;
                                     } else {
                                        showResult(gRenderer, gTextureBox, gTextureGalaxy, gTextureMar, gTextureLevelup, table, n, bombLocatX, bombLocatY, numberOfBomb, result, tmp, timewait);
                                     }
                                } else if (result == 0 || (result == oldresult && result == 1) ){
                                    Mix_HaltChannel(-1);
                                    showBombTable(gRenderer, gTextureBox, gTextureGalaxy, gTextureMar, table, n, bombLocatX, bombLocatY, numberOfBomb);
                                    Sleep(500);
                                    Mix_PlayChannel( -1, gGameOver,  0);
                                    SDL_RenderCopy( gRenderer, gTextureGameOver, NULL, NULL );
                                    SDL_RenderPresent( gRenderer );
                                    gameover = true;
                                    Sleep(7500);
                                    quit = true;
                                }
                            }
                            break;
                        }

                        }
                    }
                    if (result == 2){
                        SDL_Delay(500);
                        result = 0;
                        break;
                    }
                }


            }
		}
	}
	close();

	return 0;
}
