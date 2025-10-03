#pragma once

#include <stdint.h>
#include <stddef.h>

typedef uint32_t (*VCS_cpushader)(int, int, void*);

typedef struct VCS_dynchar {
  char c;
  VCS_cpushader fg;
  VCS_cpushader bg;
  void* fgarg;
  void* bgarg;
} VCS_dynchar_t;

VCS_dynchar_t VCS_make_dynchar(char c, VCS_cpushader fg, VCS_cpushader bg, void* fgarg, void* bgarg);

uint32_t VCS_blackshader(int x, int y, void* arg);
uint32_t VCS_whiteshader(int x, int y, void* arg);

static VCS_dynchar_t CHBLANK = (VCS_dynchar_t){' ',VCS_whiteshader,VCS_blackshader,NULL,NULL};
