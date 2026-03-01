#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

//compile with gcc mouse.c -o mouse -lSDL2

void SetPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b){
    
    SDL_LockSurface(surface);
    uint8_t* pixelArray = (uint8_t*)surface->pixels;
    pixelArray[y*surface->pitch +x*surface->format->BytesPerPixel+0] = g;
    pixelArray[y*surface->pitch +x*surface->format->BytesPerPixel+1] = b;
    pixelArray[y*surface->pitch +x*surface->format->BytesPerPixel+2] = r;
    SDL_UnlockSurface(surface);
}


int main()
{
    SDL_Window* window=NULL;

    // Grab the window surface.
    SDL_Surface* screen;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       printf("SDL could not be initialized: %s\n",SDL_GetError());
    }
    else
    {
        printf("SDL video system is ready to go\n");
    }

    window = SDL_CreateWindow("SDL2 Window",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);

    screen = SDL_GetWindowSurface(window);

    bool gameIsRunning = true;

    while(gameIsRunning)
    {
        SDL_Event event;

        int x,y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x,&y);

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                gameIsRunning= false;
            }
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                SetPixel(screen, x, y, 255, 0, 0);
            }
            if(event.button.button == SDL_BUTTON_RIGHT)
            {
                SetPixel(screen, x, y, 0, 0, 255);
            }
        }

        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return 0;
}