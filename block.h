#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>



typedef struct bomberMan
{   
    SDL_Rect bodyBox;
    SDL_Rect clip[4][3];
    int speed;
    int bomberPlaced;
    int bomberCount;
    int maxBomber;
}bomberMan;

typedef struct bomber
{    
    SDL_Rect bodyBox;
    SDL_Rect clip[4];

}bomber;

