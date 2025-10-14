#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "VCS_dynchar.h"
#include "VCS_renderpanel.h"
#include "VCS_info.h"

/**
 * Initializes SDL and all required structs for a working render loop, and passes them back in a VCS_info.
 * In a typical workflow, the main loop will hold a stack variable containing the returned VCS_info, and pass a reference to it
 * to all rendering code. At the end of the mainloop, call VCS_quit() to clean up all of the malloc'd elements of the VCS_info.
 * \param title The title that will be given to the SDL window.
 * \param width The width, in characters, of the window.
 * \param height The height, in characters, of the window.
 * \param charwidth The width, in pixels, of a single character.
 * \param charheight The height, in pixels, of a single character.
 * \param fontpath A path to the TTF font to use.
 * \return A VCS_info struct containing all relevant information for the VCS instance. Note that it is returned by value.
 * \warning Call this function only once, in the main thread, before any other VCS functions are called.
 */
VCS_info_t VCS_init(char* title, int width, int height, int charwidth, int charheight, char* fontpath);

/**
 * Draws the characters stored in `info.rp` to the texture buffers stored in `info` so that they may be rendered to the screen later.
 * Call this once, after modifying the contents of `info.rp`, to allow VCS_render() to render the updated contents.
 * Also checks the event queue to see if the application has been told to close; store and reference the return value to make sure you
 * successfully handle when the close button is pressed.
 * \param info A pointer to the VCS_info returned from VCS_init().
 * \return 0 if the application has received a quit event, 1 otherwise.
 * \note This should be called every frame, regardless of whether you have updated the character data to display. If you have shaders that animate
 * based on the passage of time, it will ensure they are redrawn every frame, and it also needs to constantly check if the application has been asked to close.
 * \warning Call this function from the main thread only.
 */
int VCS_update(VCS_info_t* info);

/**
 * Renders the texture buffers to the screen. Call this function after VCS_update() to display the next frame.
 * \param info A pointer to the VCS_info returned from VCS_init().
 * \warning Call this function from the main thread only.
 */
void VCS_render(VCS_info_t* info);

/**
 * Handles destruction of all of the fields of a VCS_info and closes the SDL window.
 * Call this function once, while the application is shutting down, to close everything.
 * \param info A pointer to the VCS_info returned from VCS_init().
 */
void VCS_quit(VCS_info_t* info);
