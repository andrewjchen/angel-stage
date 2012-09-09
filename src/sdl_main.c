#include <stdio.h>
#include "time.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

int main(int argc, char* args[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Surface * screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
  /* SDL_Surface * screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL); */

  SDL_Surface * image = IMG_Load("res/image.jpg");

  if (!image) {
    printf("Could not load image!");
  }

  SDL_BlitSurface(image, NULL, screen, NULL);

  SDL_Flip(screen);

  SDL_Delay(3000);

  SDL_Rect pos = {0, 0, 320, 240};
  SDL_Rect dest = {0, 0, 320, 240};
  int iterations = 1000;
  time_t start = time(NULL);
  for (int i = 0; i <= iterations; ++i) {
    pos.x = i % 10;
    pos.y = i % 10;
    SDL_BlitSurface(image, &pos, screen, &dest);
    SDL_Flip(screen);
  }
  time_t end = time(NULL);
  printf ("Drawing to screen %d times took %ld seconds.\n", iterations, end - start);

  iterations = 10000;
  start = time(NULL);
  for (int i = 0; i <= iterations; ++i) {
    pos.x = i % 10;
    pos.y = i % 10;
    SDL_BlitSurface(image, &pos, screen, &dest);
  }
  SDL_Flip(screen);
  end = time(NULL);
  printf ("Drawing to buffer %d times took %ld seconds.\n", iterations, end - start);

  SDL_Delay(3000);

  SDL_FreeSurface(image);

  SDL_Quit();
  return 0;
}
