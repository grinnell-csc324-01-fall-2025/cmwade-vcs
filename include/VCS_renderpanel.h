#pragma once
#include "VCS_dynchar.h"

typedef struct {
  int width;
  int height;
  VCS_dynchar_t* content;
} VCS_renderpanel_t;

void VCS_rp_init(VCS_renderpanel_t* rp, int width, int height);
VCS_renderpanel_t* VCS_make_rp(int width, int height);
void VCS_rp_set(VCS_renderpanel_t* rp, int x, int y, VCS_dynchar_t c);
void VCS_rp_drawto(VCS_renderpanel_t* source, VCS_renderpanel_t* dest, int x, int y, int transparent);
void VCS_rp_clear(VCS_renderpanel_t* rp);
void VCS_rp_free_contents(VCS_renderpanel_t* rp);
