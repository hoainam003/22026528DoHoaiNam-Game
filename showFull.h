#ifndef SHOWFULL_H
#define SHOWFULL_H

void showMenu(SDL_Renderer* gRenderer, SDL_Texture* gStartMenu);
void showBombTable(SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy, SDL_Texture* gTextureMar,
                   int* arr, int n, int *locatBombX, int *locatBombY, int bomb);
void showTable(SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy, int* arr, int n);
void showSwap(SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy,
                   int* arr, int n, int x, int y, int direction, int timewait);
void showResult(SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy, SDL_Texture* gTextureMar, SDL_Texture* gTextureLevelup,
                   int* arr, int n, int *locatBombX, int *locatBombY, int bomb, int result, int tmp, int timewait);
void showWinner(SDL_Renderer* gRenderer, SDL_Texture* gTextureCongrats);
#endif // SHOWFULL_H
