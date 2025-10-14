#pragma once

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "VCS_renderpanel.h"

/**
 * Contains references to everything relevant to the current VCS instance.
 * Created by VCS_init(), destroyed by VCS_quit().
 */
typedef struct VCS_info {
  /** Set to 0 if initialization failed somehow, 1 otherwise. Check this to make sure it's safe to proceed after VCS_init(). */
  int success;
  /** The width, in characters, of the main renderpanel. */
  int width;
  /** The height, in characters, of the main renderpanel. */
  int height;
  /** The width, in pixels, of one character. */
  int charwidth;
  /** The height, in pixels, of one character. */
  int charheight;
  /** A reference to the SDL window in which everything is drawn. */
  SDL_Window* window;
  /** A reference to the SDL renderer. */
  SDL_Renderer* renderer;
  /** A reference to the SDL texture which stores the final version of each frame. Updated by VCS_update(), and drawn to the screen by VCS_render(). */
  SDL_Texture* renderTexture;
  /** Temporary buffer used to render the foregrounds of each character. You shouldn't need to touch this. */
  uint32_t* fg;
  /** Temporary buffer used to render the backgrounds of each character. You shouldn't need to touch this. */
  uint32_t* bg;
  /** Reference to the SDL surface used to render the unshaded versions of each character from the TTF font. You shouldn't need to touch this. */
  SDL_Surface* textSurface;
  /** Reference to the TTF font loaded by SDL. */
  TTF_Font* font;
  /** Reference to SDL's text engine. */
  TTF_TextEngine* textEngine;
  /** Reference to the main renderpanel. Edit this to draw to the screen. */
  VCS_renderpanel_t* rp;
} VCS_info_t;
