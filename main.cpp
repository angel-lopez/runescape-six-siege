#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include "player.cpp"
#include "frame_clock.cpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* greenBoy = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);

bool init()
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
	}

    gWindow = SDL_CreateWindow(
        "RuneScape Six Siege",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if( gWindow == NULL )
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_RaiseWindow(gWindow);
    gScreenSurface = SDL_GetWindowSurface( gWindow );
    SDL_FillRect(
        gScreenSurface,
        NULL,
        SDL_MapRGB(gScreenSurface->format, 0, 0, 0)
    );
    return true;
}

bool loadMedia()
{
	SDL_Surface* originalGreenBoy = SDL_LoadBMP("tha_god.bmp");
	if( originalGreenBoy == NULL )
	{
		printf(
            "Unable to load image %s! SDL Error: %s\n",
            "tha_god.bmp",
            SDL_GetError()
        );
        return false;
	}

    SDL_Rect desiredShape;
    desiredShape.x = 0;
    desiredShape.y = 0;
    desiredShape.w = 50;
    desiredShape.h = 50;

    if(SDL_BlitScaled(originalGreenBoy, NULL, greenBoy, &desiredShape) != 0)
    {
        printf("Unable to scale tha_god.bmp! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_FreeSurface(originalGreenBoy);
    return true;
}

void close()
{
	SDL_FreeSurface(greenBoy);
	greenBoy = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

bool initialize()
{
    if (!init())
    {
        printf("Failed to initialize window!\n");
        return false;
    }
    
    if(!loadMedia())
    {
        printf("Failed to load media!\n");
        return false;
    }

    return true;
}



void gameLoop()
{
    bool playerHasQuit = false;
    Player player;
    FrameClock clock;

    while(!playerHasQuit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    playerHasQuit = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_W) { player.velocity.y = -200; }
                    if (event.key.keysym.scancode == SDL_SCANCODE_A) { player.velocity.x = -200; }
                    if (event.key.keysym.scancode == SDL_SCANCODE_S) { player.velocity.y = 200; }
                    if (event.key.keysym.scancode == SDL_SCANCODE_D) { player.velocity.x = 200; }
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.scancode == SDL_SCANCODE_S)
                    {
                        player.velocity.y = 0;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.scancode == SDL_SCANCODE_D)
                    {
                        player.velocity.x = 0;
                    }
                    break;
                default:
                    break;
            }
        }

        double timeElapsedInSeconds = clock.measureFrameTimeInSeconds();
        
        player.move(timeElapsedInSeconds);

        if (player.coordinates.x < 0) { player.coordinates.x = 0; }
        if (player.coordinates.x > SCREEN_WIDTH - 50) { player.coordinates.x = SCREEN_WIDTH - 50; }
        if (player.coordinates.y < 0) { player.coordinates.y = 0; }
        if (player.coordinates.y > SCREEN_HEIGHT - 50) { player.coordinates.y = SCREEN_HEIGHT - 50; }

        SDL_Rect endPlacement;
        endPlacement.x = player.coordinates.x;
        endPlacement.y = player.coordinates.y;
        endPlacement.w = 50;
        endPlacement.h = 50;

        SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));

        SDL_BlitSurface( greenBoy, NULL, gScreenSurface, &endPlacement );
        SDL_UpdateWindowSurface( gWindow );
    }
}

int main( int argc, char* args[] )
{
    if(initialize())
    {
        gameLoop();
    }
    else
    {
        printf("Could not initialize program, exiting.\n");
    }

	close();
}
