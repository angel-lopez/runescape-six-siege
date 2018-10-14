#include <SDL2/SDL.h>
#include <string>

#if !defined(ENTITY)
#define ENTITY

class Entity
{
public:
  struct { double x = 0; double y = 0; } coordinates;
  struct { int x = 0; int y = 0; } velocity;
  struct { int width = 0; int height = 0; } dimensions;
  SDL_Surface* visual;
  Entity(std::string imagePath, int startingWidth, int startingHeight, int startingX, int startingY);
  ~Entity();
  void move(double time);
  void setXVelocity(int velocity);
  void setYVelocity(int velocity);
};

Entity::Entity(std::string imagePath, int startingWidth, int startingHeight, int startingX, int startingY)
{
  SDL_Surface* entityAsset = SDL_LoadBMP(imagePath.c_str());
	if(entityAsset == NULL)
	{
		printf(
      "Unable to load image %s! SDL Error: %s\n",
      "tha_god.bmp",
      SDL_GetError()
    );
    throw;
	}

  SDL_Rect desiredShape;
  desiredShape.x = startingX;
  desiredShape.y = startingY;
  desiredShape.w = startingWidth;
  desiredShape.h = startingHeight;

  visual = SDL_CreateRGBSurface(0, startingWidth, startingHeight, 32, 0, 0, 0, 0);
  if(SDL_BlitScaled(entityAsset, NULL, visual, &desiredShape) != 0)
  {
      printf("Unable to scale tha_god.bmp! SDL Error: %s\n", SDL_GetError());
      throw;
  }

  SDL_FreeSurface(entityAsset);
}

Entity::~Entity() {
  SDL_FreeSurface(visual);
}

void Entity::move(double time)
{
  coordinates.x += velocity.x * time;
  coordinates.y += velocity.y * time;
}

#endif // ENTITY
