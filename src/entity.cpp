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
  Entity(SDL_Surface* entityAsset, int startingWidth, int startingHeight, int startingX, int startingY);
  ~Entity();
  void move(double time);
  void setXVelocity(int velocity);
  void setYVelocity(int velocity);
};

Entity::Entity(SDL_Surface* entityAsset, int startingWidth, int startingHeight, int startingX, int startingY)
{
  dimensions.width = startingWidth;
  dimensions.height = startingHeight;
  coordinates.x = startingX;
  coordinates.y = startingY;

  SDL_Rect desiredShape;
  desiredShape.x = 0;
  desiredShape.y = 0;
  desiredShape.w = startingWidth;
  desiredShape.h = startingHeight;

  visual = SDL_CreateRGBSurface(0, startingWidth, startingHeight, 32, 0, 0, 0, 0);
  if(SDL_BlitScaled(entityAsset, NULL, visual, &desiredShape) != 0)
  {
      printf("Unable to scale tha_god.bmp! SDL Error: %s\n", SDL_GetError());
      throw;
  }
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
