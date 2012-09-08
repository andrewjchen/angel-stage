#include "allegro5/allegro.h"
#include "stdio.h"

const int scrx = 640;
const int scry = 480;

int main(int argc, char* argv[]) {
  if (!al_init()) {
    printf("Cannot initalize Allegro.\n");
    return 1;
  }
  ALLEGRO_DISPLAY * display = al_create_display(800, 600);

  //Set the window title when in a GUI environment
  al_set_window_title(display, "Hello World");

  if (!al_install_keyboard()) {
    printf("Cannot initalize keyboard input.\n");
    return 1;
  }

  int scratch;
  printf("Enter number to quit:");
  scanf("%d", &scratch);

  return 0;
  //Allegro will automatically deinitalize itself on exit
}
