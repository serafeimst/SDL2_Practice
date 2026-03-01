#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// needs libsdl2-image-dev
// compile with gcc image.c -o image -lSDL2 -lSDL2_image -ldl

int main(int argc, char* argv[]){
   
    SDL_Window* window=NULL;
    SDL_Renderer* renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       printf("SDL could not be initialized: %s\n",SDL_GetError());
    }
    else
    {
        printf("SDL video system is ready to go\n");
    }

    window = SDL_CreateWindow("SDL2 Window",
            0,
            0,
            640,
            480,
            SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);

    if((initStatus & flags) != flags)
    {
        printf("SDL2_Image format not available\n");
    }

    SDL_Surface* image;
    image = IMG_Load("./images/ball.bmp");

    if(!image)
    {
        printf("Image not loaded...\n");
    }

    SDL_Texture* myPNG = SDL_CreateTextureFromSurface(renderer, image);
    bool gameIsRunning = true;

    while(gameIsRunning)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                gameIsRunning= false;
            }

        }
        
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,myPNG,NULL,NULL);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_FreeSurface(image);
    SDL_DestroyTexture(myPNG);
    IMG_Quit();
    SDL_Quit();

    return 0;
}