#include "VCS_dynchar.h"

VCS_dynchar_t VCS_make_dynchar(char c, VCS_cpushader fg, VCS_cpushader bg, void* fgarg, void* bgarg) {
  VCS_dynchar_t newchar;
  newchar.c = c;
  newchar.fg = fg;
  newchar.bg = bg;
  newchar.fgarg = fgarg;
  newchar.bgarg = bgarg;
  return newchar;
}

uint32_t VCS_blackshader(int x, int y, void* arg) { return 0xff000000; }
uint32_t VCS_whiteshader(int x, int y, void* arg) { return 0xffffffff; }
