#include "RenderSetup.hxx"
#include "ClientGlobals.hxx"

bool setup_rendering() {
	if (!al_init() || !al_init_image_addon())
	{
		printf("Cannot initalize Allegro.\n");
		return 0; // Fail.
	}
	display = al_create_display(display_width, display_height);
	al_set_target_backbuffer(display);
	return 1;
}
