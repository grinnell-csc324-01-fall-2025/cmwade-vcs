/*
 * A demo of using the VCS framework
 * with SDL to render a simple scene.
 */

#include <ctype.h>
#include <math.h>
#include "VCS/VCS.h"

uint32_t blinkblueshader(int x, int y, void* arg) {
  int ticks = *(int*)arg/75;
  double sinticks = (sin(ticks)+1)/2*255;
  return 0xff000000 | (0x00010000 * (int)sinticks);
}

int main() {
  VCS_info_t info = VCS_init("Welcome to VCS", 5, 5, "./8x16.ttf");
  int ticks;

  VCS_rp_set(info.rp, 2, 1, VCS_make_dynchar('N',VCS_whiteshader,VCS_blackshader,NULL,NULL));
  VCS_rp_set(info.rp, 3, 2, VCS_make_dynchar('E',VCS_whiteshader,VCS_blackshader,NULL,NULL));
  VCS_rp_set(info.rp, 1, 2, VCS_make_dynchar('W',VCS_whiteshader,VCS_blackshader,NULL,NULL));
  VCS_rp_set(info.rp, 2, 3, VCS_make_dynchar('S',VCS_whiteshader,VCS_blackshader,NULL,NULL));
  VCS_rp_set(info.rp, 2, 2, VCS_make_dynchar('+',blinkblueshader,VCS_blackshader,(void*)&ticks,NULL));

  while (VCS_update(&info)) {
    ticks++;
    VCS_render(&info);
  }

  VCS_quit(&info);
}
