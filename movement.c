#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// compile with gcc movement.c -o movement -lSDL2 -ldl

int main()
{
    SDL_Window* window=NULL;
    SDL_Renderer* renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       printf("SDL could not be initialized: %s\n",SDL_GetError());
    }
   
    window = SDL_CreateWindow("SDL2 Window",
            0,
            0,
            640,
            480,
            SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    SDL_Surface* surface = SDL_LoadBMP("./images/kong.bmp");
 
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0xFF,0,0xFF));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface); 

    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 100;
    rectangle.w = 200;
    rectangle.h = 200;

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

            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_w)
                {
                    rectangle.y -= 3;
                }
                
                if(event.key.keysym.sym == SDLK_s)
                {
                    rectangle.y += 3;
                }

                if(event.key.keysym.sym == SDLK_d)
                {
                    rectangle.x += 3;
                }
                
                if(event.key.keysym.sym == SDLK_a)
                {
                    rectangle.x -= 3;
                }
            }
        }
       
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
       
        SDL_RenderCopy(renderer,texture,NULL,&rectangle);
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}