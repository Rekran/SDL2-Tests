#include "block.h"
#include "texture.h"
int height = 600;
int width = 800;

//Inicialização
int main(int argc, char **argv)
{
int iW = 32, iH = 32;
//Setup the clips for our image

bomber bomber;
bomberMan player;

player.bodyBox.x = 0;
player.bodyBox.y = 0;
player.bodyBox.h = iW*3;
player.bodyBox.w = iH*3;

for(int j = 0;j < 4;j++){
  for (int i = 0;i < 3;i++){
    player.clip[j][i].x = i * 32;
    player.clip[j][i].y = j * 32;
    player.clip[j][i].h = iW;
    player.clip[j][i].w = iH;
  }
}
int select = 0;

player.bomberPlaced = 0;
player.bomberCount = 0;
player.maxBomber = 1;
player.speed = 5;

bomber.bodyBox.h = iH*4;
bomber.bodyBox.w = iW*4;


bomber.clip[0].x = 0;
bomber.clip[0].y = 0;
bomber.clip[0].h = iH/2;
bomber.clip[0].w = iW/2;
int frame = 0;
IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    SDL_Log("Can't init %s", SDL_GetError());

SDL_Window * window =  SDL_CreateWindow("Teste", 100, 100, width, height, 0);
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

SDL_Texture *playerTexture = loadTexture("Bomberman4.png",renderer);
SDL_Texture *bomberTexture = loadTexture("Bomber.png",renderer);

//Inicialização
int running = 1;
 
//Gameloop
while(running)
{
  ///Logica
  //Detecção de Evento
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT: //Caso saia
            running = 0;
            break;
        }
    }

const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

SDL_PollEvent(&event);

if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
{   

    if(keyboard_state_array[SDL_SCANCODE_SPACE]){
      
      if(player.maxBomber >  player.bomberCount){
        player.bomberPlaced = 1;
        player.bomberCount += 1;
        bomber.bodyBox.x = player.bodyBox.x + (player.bodyBox.w/2);
        bomber.bodyBox.y = player.bodyBox.y + (player.bodyBox.h/2);
      }
    }
    if (keyboard_state_array[SDL_SCANCODE_UP] && !keyboard_state_array[SDL_SCANCODE_DOWN])
    {
      player.bodyBox.y -= player.speed;
      if(select == 0)
        frame++;
      else
      {
        frame = 0;
      }
      select = 0;
      if(frame/3 >= 3)
        frame = 0;
    }
    else if (!keyboard_state_array[SDL_SCANCODE_UP] && keyboard_state_array[SDL_SCANCODE_DOWN])
    {
      player.bodyBox.y+= player.speed;
      if(select == 2)
        frame++;
      else
      {
        frame = 0;
      }
      select = 0;
      if(frame/3 >= 3)
        frame = 0;

      select = 2;
    }
    else if (keyboard_state_array[SDL_SCANCODE_LEFT] && !keyboard_state_array[SDL_SCANCODE_RIGHT])
    {
      player.bodyBox.x -= player.speed;
      if(select == 3)
        frame++;
      else
      {
        frame = 0;
      }
      select = 3;

      if(frame/3 >= 3)
        frame = 0;

      select = 3;
    }
    else if (!keyboard_state_array[SDL_SCANCODE_LEFT] && keyboard_state_array[SDL_SCANCODE_RIGHT])
    {
      player.bodyBox.x += player.speed;
      if(select == 1)
        frame++;
      else
      {
        frame = 0;
      }
      select = 0;
      if(frame/3 >= 3)
        frame = 1;

      select = 1;
    }
    else
    {
      if(frame/3 != 0)
        frame--;
      if(frame/3 != 0)
        frame--;
        
    }
    

}

///Rendering vai vir aqui
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  if(player.bomberPlaced)
    SDL_RenderCopy(renderer,bomberTexture,&bomber.clip[0],&bomber.bodyBox);

  SDL_SetRenderDrawColor(renderer,255, 255,255,255);
  SDL_RenderCopy(renderer,playerTexture,&player.clip[select][frame/3],&player.bodyBox);
  SDL_RenderPresent(renderer);

//Não vá tão rápido!
  SDL_Delay(40); //Isso causa algo como 60 quadros por segundo.

  
}

    //Free loaded image
    SDL_DestroyTexture( playerTexture );
    SDL_DestroyTexture( bomberTexture );
    playerTexture = NULL;
    bomberTexture = NULL;

    //Destroy window    
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

  return 0;
}