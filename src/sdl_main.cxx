#include <iostream>
#include "SDL/SDL.h"

int main(int argc, char* args[]) {
  std::cout << "This is a test.\n";
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Surface * screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);

  SDL_Surface * image = SDL_LoadBMP("../../../resources/image.jpg");

  SDL_BlitSurface(image, NULL, screen, NULL);

  SDL_Flip(screen);

  SDL_Delay(3000);

  SDL_FreeSurface(image);

  SDL_Quit();
  return 0;
}
