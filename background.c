#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define MIN(x,y) ((x) < (y) ? (x) : (y))

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
    int x, y;
    int fixed=126;

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

    // Main application loop
    while(gameIsRunning)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                gameIsRunning= false;
            }
           
             for( y = 0; y < 240;y++) 
             {
                for( x = 0; x < 640;x++) 
                {
                    SetPixel(screen, x, y, MIN(fixed,y),fixed,MIN(fixed,y)); //red blue green
                }
            }

             for( y = 240; y < 480;y++) 
             {
                for( x = 0; x < 640;x++) 
                {
                    SetPixel(screen, x, y, 10,10,(y-200)/2); //red blue green
                }
            }
        }

        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return 0;
}