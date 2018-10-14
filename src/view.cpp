#include <SDL2/SDL.h>
#include "entity.cpp"

#if !defined(VIEW)
#define VIEW

class View
{
private:
  SDL_Window* window;
  SDL_Surface* renderCanvas;
  void clearRender();
public:
  View();
  ~View();
  bool initialize(int viewWidth, int viewHeight);
  void render(Entity* entity);
  void draw();
};

View::View()
{
}

View::~View()
{
  SDL_FreeSurface(renderCanvas);
  SDL_DestroyWindow(window);
}

void View::clearRender()
{
  SDL_FillRect(renderCanvas, NULL, SDL_MapRGB(renderCanvas->format, 0, 0, 0));
}

bool View::initialize(int viewWidth, int viewHeight)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  window = SDL_CreateWindow(
    "RuneScape Six Siege",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    viewWidth,
    viewHeight,
    SDL_WINDOW_SHOWN
  );

  if (window == NULL)
  {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  renderCanvas = SDL_GetWindowSurface(window);
  clearRender();
  SDL_RaiseWindow(window);
  return true;
}

void View::render(Entity* entity)
{
  SDL_Rect endPlacement;
  endPlacement.x = entity->coordinates.x;
  endPlacement.y = entity->coordinates.y;
  endPlacement.w = entity->dimensions.width;
  endPlacement.h = entity->dimensions.height;
  SDL_BlitSurface(entity->visual, NULL, renderCanvas, &endPlacement);
}

void View::draw()
{
  SDL_UpdateWindowSurface(window);
  clearRender();
}

#endif // VIEW
