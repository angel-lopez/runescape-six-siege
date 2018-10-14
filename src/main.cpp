#include <SDL2/SDL.h>
#include <stdio.h>

#include "view.cpp"
#include "frame_clock.cpp"
#include "entity.cpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

View view;

void close()
{
    view.~View();
	SDL_Quit();
}

bool initialize()
{
    if (!view.initialize(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        printf("Failed to initialize window!\n");
        return false;
    }

    return true;
}

void gameLoop()
{
    bool playerHasQuit = false;

    SDL_Surface* testImage = SDL_LoadBMP("../assets/tha_god.bmp");
    if(testImage == NULL)
	{
		printf(
            "Unable to load image %s! SDL Error: %s\n",
            "tha_god.bmp",
            SDL_GetError()
        );
        throw;
	}

    Entity player(testImage, 50, 50, 0, 0);
    Entity platform(testImage, 400, 50, 120, 300);
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

        if (player.coordinates.x < 0) {
            player.coordinates.x = 0;
        }

        
        if (player.coordinates.x > SCREEN_WIDTH - 50) {
            player.coordinates.x = SCREEN_WIDTH - 50;
        }
        
        if (player.coordinates.y < 0) {
            player.coordinates.y = 0;
        }
        
        if (player.coordinates.y > SCREEN_HEIGHT - 50) {
            player.coordinates.y = SCREEN_HEIGHT - 50;
        }
        
        view.render(&player);
        view.render(&platform);
        view.draw();
    }
}

int main(int argc, char* args[])
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
