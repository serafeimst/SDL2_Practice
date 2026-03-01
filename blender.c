#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// compile with gcc blender.c -o blender -lSDL2 -ldl

int main(int argc, char* argv[])
{
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

    SDL_Surface* surface = SDL_LoadBMP("./images/kong.bmp");
 
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0xFF,0,0xFF));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface); 

    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 100;
    rectangle.w = 200;
    rectangle.h = 200;

    SDL_Rect rectangle2;
    rectangle2.x = 50;
    rectangle2.y = 100;
    rectangle2.w = 200;
    rectangle2.h = 200;

    bool gameIsRunning = true;

    while(gameIsRunning)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            // Handle each specific event
            if(event.type == SDL_QUIT)
            {
                gameIsRunning= false;
            }

            if(event.type == SDL_MOUSEMOTION)
            {
                rectangle2.x = event.motion.x;
                rectangle2.y = event.motion.y;
            }

            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_ADD);
                }
                else if(event.button.button == SDL_BUTTON_MIDDLE)
                {
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_MOD);
                }

            }
            else
            {
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_NONE);
            }
        }
       
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer,5,5,200,220);

        SDL_RenderCopy(renderer,texture,NULL,&rectangle);
        SDL_RenderCopy(renderer,texture,NULL,&rectangle2);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}