#include "color.h"
#include "logging.h"
#include "sprite/Sprite.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#define TITLE "NewSDLGame"
#define WIDTH 400
#define HEIGHT 400

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
bool gameRunning = true;
std::vector<Sprite*> sprites;

int init();
int graceful_exit();
void render();

int main(int argc, char const *argv[]) {
  if (init() != 0) {
    ERROR("init failed");
    return -1;
  }
  DEBUG("Init'd");
  Sprite* box = new Sprite(gRenderer);
  box->gColor = RED;
  sprites.push_back(box);
  while (gameRunning) {
    SDL_Event *evt = new SDL_Event;
    while (SDL_PollEvent(evt)) {
      switch (evt->type) {
      case SDL_QUIT:
        gameRunning = false;
        break;
      }
    }
    render();
  }

  return graceful_exit();
}
int init() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    ERROR("SDL_Init failed");
    return -1;
  }
  DEBUG("SDL init'd");
  gWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  if (gWindow == NULL) {
    ERROR("gWindow is null");
    return -1;
  }
  DEBUG("Window made");

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (gRenderer == NULL) {
    ERROR("gRenderer is null");
  }

  return 0;
}
int graceful_exit() {
  SDL_Quit();
  return 0;
}

void render() {
  SDL_SetRenderDrawColor(gRenderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
  SDL_RenderClear(gRenderer);
  SDL_RenderPresent(gRenderer);
  
  for(Sprite* s: sprites){
    DEBUG(s->dstRect.x);
    DEBUG(s->dstRect.y);
    DEBUG(s->dstRect.w);
    DEBUG(s->dstRect.h);
    SDL_RenderCopy(gRenderer,s->render(),&s->sourceRect,&s->dstRect);
  
  }
}
