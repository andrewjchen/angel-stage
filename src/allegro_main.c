#include "stdio.h"
#include "time.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

int main(int argc, char* argv[]) {

  if (!al_init() || !al_init_image_addon()) {
    printf("Cannot initalize Allegro.\n");
    return 1;
  }

  ALLEGRO_DISPLAY * display = al_create_display(800, 600);
  ALLEGRO_BITMAP * image = al_load_bitmap("res/image.jpg");

  if (!image) {
    printf ("Could not load image!\n");
  }

  al_set_target_backbuffer(display);

  al_draw_bitmap(image, 0.0, 0.0, 0);
  al_flip_display();

  int iterations = 1000;
  time_t start = time(NULL);
  for (int i = 0; i <= iterations; ++i) {
    al_draw_bitmap(image, i % 10, i % 10, 0);
    al_flip_display();
  }
  time_t end = time(NULL);
  printf ("Drawing to screen %d times took %ld seconds.\n", iterations, end - start);

  iterations = 1000000;
  start = time(NULL);
  for (int i = 0; i <= iterations; ++i) {
    al_draw_bitmap(image, i % 10, i % 10, 0);
  }
  al_flip_display();
  end = time(NULL);
  printf ("Drawing to buffer %d times took %ld seconds.\n", iterations, end - start);

  al_rest(3.0);

  return 0;
}
