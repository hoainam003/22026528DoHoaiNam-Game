#ifndef GENERATE_H
#define GENERATE_H

int *generateTable(int n, int bomb, int *locatBombX, int *locatBombY);
void switchBomb(int* table, int n, int* bombLocatX, int* bombLocatY, int numberOfBomb,
                SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy, int timewait);

#endif // GENERATE_H
