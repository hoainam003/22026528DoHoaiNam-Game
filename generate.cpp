#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include "showFull.h"
#include "generate.h"

int *generateTable(int n, int bomb, int *locatBombX, int *locatBombY)
{
    int *a = new int[n*n];
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            a[i*n+j] = 0;

    srand(time(NULL));
    for (int i=0; i<bomb; i++) {
        int random_x = rand() % (n-1) + 0;
        int random_y = rand() % (n-1) + 0;
        if (a[random_x*n + random_y] == 1) {
            i --;
        } else {
            a[random_x*n + random_y] = 1;
            *(locatBombX + i) = random_x;
            *(locatBombY + i) = random_y;
        }
    }
    return a;
}

void switchBomb(int* table, int n, int* bombLocatX, int* bombLocatY, int numberOfBomb,
                SDL_Renderer* gRenderer, SDL_Texture* gTextureBox, SDL_Texture* gTextureGalaxy, int timewait)
{
    int i = 0;
    while (i < 8) {
        srand(time(NULL));
        int randomBomb = rand() % (numberOfBomb) + 0;
        int a = *(bombLocatX + randomBomb), b = *(bombLocatY + randomBomb);
        int randSwap = rand() % 3 + 1;
        if (randSwap == 1 && b == n-1)randSwap = 3;
        if (randSwap == 2 && a == n-1)randSwap = 4;
        if (randSwap == 3 && b == 0)randSwap = 1;
        if (randSwap == 4 && a == 0)randSwap = 2;

        if (randSwap == 1) {
            if (table[a*n + b+1] == 0) {
                std::swap( table[a*n + b], table[a*n + b+1] );
                *(bombLocatY + randomBomb) += 1;
            }
            showSwap(gRenderer, gTextureBox, gTextureGalaxy, table, n, b, a, randSwap, timewait);
            i++;
        } else if (randSwap == 2) {
            if (table[(a+1)*n + b] == 0) {
                std::swap( table[a*n + b], table[(a+1)*n + b] );
                *(bombLocatX + randomBomb) += 1;
            }
            i++;
            showSwap(gRenderer, gTextureBox, gTextureGalaxy, table, n, b, a, randSwap, timewait);
        } else if (randSwap == 3) {
            if (table[a*n + b-1] == 0) {
                std::swap( table[a*n + b], table[a*n + b-1] );
                *(bombLocatY + randomBomb) -= 1;
            }
            i++;
            showSwap(gRenderer, gTextureBox, gTextureGalaxy, table, n, b-1, a, 1, timewait);
        } else if (randSwap == 4) {
            if (table[(a-1)*n + b] == 0) {
                std::swap( table[a*n + b], table[(a-1)*n + b] );
                *(bombLocatX + randomBomb) -= 1;
            }
            i++;
            showSwap(gRenderer, gTextureBox, gTextureGalaxy, table, n, b, a-1, 2, timewait);
        }
    }
}
