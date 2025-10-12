#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "VCS_dynchar.h"
#include "VCS_renderpanel.h"
#include "VCS_info.h"

VCS_info_t VCS_init(char* title, int width, int height, int charwidth, int charheight, char* fontpath);
int VCS_update(VCS_info_t* info);
void VCS_render(VCS_info_t* info);
void VCS_quit(VCS_info_t* info);
