#include <SDL.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* greenBoy = NULL;

bool init()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
            SDL_RaiseWindow(gWindow);
			gScreenSurface = SDL_GetWindowSurface( gWindow );
            SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	greenBoy = SDL_LoadBMP( "tha_god.bmp" );
	if( greenBoy == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
		success = false;
	}
	return success;
}

void close()
{
	SDL_FreeSurface( greenBoy );
	greenBoy = NULL;

	SDL_DestroyWindow( gWindow );
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
                    std::cout << SDL_GetScancodeName(event.key.keysym.scancode) << std::endl;
                    break;
                default:
                    break;
            }
        }

        SDL_BlitSurface( greenBoy, NULL, gScreenSurface, NULL );
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
