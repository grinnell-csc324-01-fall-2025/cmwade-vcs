#include <stdlib.h>
#include <stdbool.h>

#include "VCS_dynchar.h"
#include "VCS_renderpanel.h"

void VCS_rp_init(VCS_renderpanel_t* rp, int width, int height) {
  rp->width = width;
  rp->height = height;
  rp->content = (VCS_dynchar_t*)malloc(sizeof(VCS_dynchar_t) * width * height);
  for (int i = 0; i < width*height; i++) {rp->content[i] = CHBLANK;}
}

VCS_renderpanel_t* VCS_make_rp(int width, int height) {
  VCS_renderpanel_t* rp = (VCS_renderpanel_t*)malloc(sizeof(VCS_renderpanel_t));
  VCS_rp_init(rp, width, height);
  return rp;
}

void VCS_rp_set(VCS_renderpanel_t* rp, int x, int y, VCS_dynchar_t c) {
  rp->content[(y*rp->width)+x] = c;
}

void VCS_rp_drawto(VCS_renderpanel_t* source, VCS_renderpanel_t* dest, int x, int y, int transparent) {
  int destx, desty;
  VCS_dynchar_t * c;
  for (int i = 0; i < source->width*source->height; i++) {
    desty = i / source->width + y;
    destx = i % source->width + x;
    c = source->content + i;

    if (!transparent || c->c != ' ') {VCS_rp_set(dest,destx,desty,*c);}
  }
}

void VCS_rp_clear(VCS_renderpanel_t* rp) {
  for (int i = 0; i < (rp->width)*(rp->height); i++) {
    rp->content[i] = CHBLANK;
  }
}

void VCS_rp_free_contents(VCS_renderpanel_t* rp) {
  free(rp->content);
}
