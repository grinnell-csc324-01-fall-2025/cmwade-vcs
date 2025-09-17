/*
 * A demo of using the VCS framework
 * with SDL to render a simple scene.
 */

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "VCS.h"

// Initialize window
// VCS initializes surfaces, textures, renderers, whatever
// VCS gives you a pointer to an array of {char, foreground, background}
// Write to the character array
// In a loop:
//  Draw
