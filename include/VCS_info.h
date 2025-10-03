#pragma once

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "VCS_renderpanel.h"

typedef struct VCS_info {
  int success;
  int width;
  int height;
  int charwidth;
  int charheight;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* renderTexture;
  uint32_t* fg;
  uint32_t* bg;
  SDL_Surface* textSurface;
  TTF_Font* font;
  TTF_TextEngine* textEngine;
  VCS_renderpanel_t* rp;
} VCS_info_t;
