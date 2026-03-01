#include <stdio.h>
#include <SDL2/SDL.h>

int main()
{
    SDL_Window* window=NULL;

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

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return 0;
}