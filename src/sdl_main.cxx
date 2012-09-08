#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

int main(int argc, char* args[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Surface * screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);

  SDL_Surface * image = IMG_Load("res/image.jpg");

  if (!image) {
    std::cout << "Could not load image!";
  }

  SDL_BlitSurface(image, NULL, screen, NULL);

  SDL_Flip(screen);

  SDL_Delay(1000);

  SDL_FreeSurface(image);

  SDL_Quit();
  return 0;
}
