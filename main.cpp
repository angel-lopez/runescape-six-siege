#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <chrono>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* greenBoy = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);

std::chrono::high_resolution_clock::time_point lastFrameTime;
double gameLength = 0.00;

bool init()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "RuneScape Six Siege", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	SDL_Surface* originalGreenBoy = SDL_LoadBMP( "tha_god.bmp" );
	if( originalGreenBoy == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
		success = false;
	}

    SDL_Rect desiredShape;
    desiredShape.x = 0;
    desiredShape.y = 0;
    desiredShape.w = 50;
    desiredShape.h = 50;

    if(SDL_BlitScaled(originalGreenBoy, NULL, greenBoy, &desiredShape) != 0)
    {
        printf("fuck lmao: %s\n", SDL_GetError());
        success = false;
    }

    SDL_FreeSurface(originalGreenBoy);
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
    lastFrameTime = std::chrono::high_resolution_clock::now();

    double playerX = 0;
    double playerY = 0;
    int playerXVelocity = 0;
    int playerYVelocity = 0;

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
                    if (event.key.keysym.scancode == SDL_SCANCODE_W) { playerYVelocity = -100; }
                    if (event.key.keysym.scancode == SDL_SCANCODE_A) { playerXVelocity = -100; }
                    if (event.key.keysym.scancode == SDL_SCANCODE_S) { playerYVelocity = 100; }
                    if (event.key.keysym.scancode == SDL_SCANCODE_D) { playerXVelocity = 100; }
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.scancode == SDL_SCANCODE_S)
                    {
                        playerYVelocity = 0;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.scancode == SDL_SCANCODE_D)
                    {
                        playerXVelocity = 0;
                    }
                    break;
                default:
                    break;
            }
        }

        std::chrono::high_resolution_clock::time_point currentFrameTime = std::chrono::high_resolution_clock::now();
        auto timeElapsedSinceLastFrame = currentFrameTime - lastFrameTime;
        int timeElapsedInMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(timeElapsedSinceLastFrame).count();
        double timeElapsedInSeconds = timeElapsedInMicroseconds / (double)1000000;
        lastFrameTime = currentFrameTime;

        gameLength += timeElapsedInSeconds;

        // std::cout << timeElapsedInMicroseconds << std::endl;
        // std::cout << timeElapsedInSeconds << std::endl;
        std::cout << gameLength << std::endl;

        playerX += playerXVelocity * timeElapsedInSeconds;
        playerY += playerYVelocity * timeElapsedInSeconds;

        // std::cout << playerX << std::endl;

        if (playerX < 0) { playerX = 0; }
        if (playerX > SCREEN_WIDTH - 50) { playerX = SCREEN_WIDTH - 50; }
        if (playerY < 0) { playerY = 0; }
        if (playerY > SCREEN_HEIGHT - 50) { playerY = SCREEN_HEIGHT - 50; }

        SDL_Rect endPlacement;
        endPlacement.x = playerX;
        endPlacement.y = playerY;
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
