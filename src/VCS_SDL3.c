#include <stdlib.h>

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "VCS_SDL3.h"
#include "VCS_dynchar.h"
#include "VCS_renderpanel.h"
#include "VCS_info.h"

VCS_info_t VCS_init(char* title, int width, int height, char* fontpath) {
  VCS_info_t info;
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) || !TTF_Init()) {
    info.success = 0;
    return info;
  }

  info.success = 1;
  info.charwidth = 8;  /* Hardcoded for now */
  info.charheight = 8; /*                   */
  info.width = width;
  info.height = height;
  int windowwidth = width*info.charwidth;
  int windowheight = height*info.charheight;
  info.window = SDL_CreateWindow(title, windowwidth, windowheight, 0);
  info.renderer = SDL_CreateRenderer(info.window, NULL);
  info.renderTexture = SDL_CreateTexture(info.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, windowwidth, windowheight);
  info.fg = malloc(sizeof(uint32_t) * windowwidth * windowheight);
  info.bg = malloc(sizeof(uint32_t) * windowwidth * windowheight);
  info.textSurface = SDL_CreateSurface(windowwidth, windowheight, SDL_PIXELFORMAT_ABGR8888);
  info.font = TTF_OpenFont(fontpath, info.charwidth);
  info.textEngine = TTF_CreateSurfaceTextEngine();
  info.rp = VCS_make_rp(width, height);

  // TODO: Also validate all of these and fail if they are not created properly

  // TODO: Make SDL initialization optional
  SDL_SetWindowFullscreen(info.window, 1);
  SDL_SetRenderLogicalPresentation(info.renderer, windowwidth, windowheight,  SDL_LOGICAL_PRESENTATION_LETTERBOX);
  SDL_SetTextureScaleMode(info.renderTexture, SDL_SCALEMODE_NEAREST);

  return info;
}

int VCS_update(VCS_info_t* info) {
  SDL_Event e;
  if (SDL_PollEvent(&e))
  {
    if (e.type == SDL_EVENT_QUIT)
    {
      return 0;
    }
  }

  SDL_ClearSurface(info->textSurface, 0, 0, 0, 0);
  char str[] = {' ', '\0'};
  TTF_Text* text;
  for (int x = 0; x < info->width*info->charwidth; x += info->charwidth) {
    for (int y = 0; y < info->height*info->charheight; y += info->charheight) {
      int charx = x/8;
      int chary = y/8;
      str[0] = info->rp->content[(chary*info->width + charx)].c;
      text = TTF_CreateText(info->textEngine, info->font, str, 1);
      TTF_DrawSurfaceText(text, x, y, info->textSurface);
    }
  }
  TTF_DestroyText(text);

  uint32_t* pix;
  int pitch;
  
  SDL_LockTexture(info->renderTexture, NULL, (void**)&pix, &pitch);
  SDL_LockSurface(info->textSurface);

  uint32_t* surfacePixels = (uint32_t*)(info->textSurface->pixels);
  
  for (int i = 0; i < info->width*info->charwidth * info->height*info->charheight; i++) {
    int x = i % (info->width*info->charwidth);
    int y = i / (info->width*info->charwidth);
    int charx = x/8;
    int chary = y/8;
    VCS_cpushader fgshader = info->rp->content[(chary*info->width + charx)].fg;
    VCS_cpushader bgshader = info->rp->content[(chary*info->width + charx)].bg;
    void* fgarg = info->rp->content[(chary*info->width + charx)].fgarg;
    void* bgarg = info->rp->content[(chary*info->width + charx)].bgarg;
    if (surfacePixels[i] & 0xff000000) {
      pix[i] = fgshader(x, y, fgarg);
    }
    else {
      pix[i] = bgshader(x, y, bgarg);
    }
  }

  SDL_UnlockTexture(info->renderTexture);
  SDL_UnlockSurface(info->textSurface);

  return 1;
}

void VCS_render(VCS_info_t* info) {
  SDL_RenderClear(info->renderer);
  SDL_RenderTexture(info->renderer, info->renderTexture, NULL, NULL);
		    
  SDL_RenderPresent(info->renderer);
  SDL_Delay(1);
}

void VCS_quit(VCS_info_t* info) {
  SDL_DestroyTexture(info->renderTexture);
  SDL_DestroyRenderer(info->renderer);
  SDL_DestroyWindow(info->window);
  // TODO: More stuff to destroy here
  TTF_Quit();
  SDL_Quit();
}
