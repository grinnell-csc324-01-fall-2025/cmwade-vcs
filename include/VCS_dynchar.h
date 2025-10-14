#pragma once

#include <stdint.h>
#include <stddef.h>

/**
 * \typedef VCS_cpushader
 * A function pointer type which matches the expected signature of
 * a VCS_dynchar's shader. Any shaders you write yourself must
 * conform to this format.
 * \public \relates VCS_dynchar
 * \param[in] x The x position of the pixel being drawn relative to the top-left of the character's grid square.
 * \param[in] y The y position of the pixel being drawn relative to the top-left of the character's grid square.
 * \param[in] arg A void pointer to an argument, or NULL. What is passed here depends on VCS_dynchar.fgarg and VCS_dynchar.bgarg.
 * \return A  uint32_t representing a color in ABGR8888 format.
 *
 * This example shows how to define a shader that renders a uniform dark blue:
 * \code
 * uint32_t darkblueshader(int x, int y, void* arg) { 
 *  return 0xff550000;
 * }
 * \endcode
 */
typedef uint32_t (*VCS_cpushader)(int, int, void*);

/**
 * A "dynamic character" used to specify a given character along with how to render its foreground
 * and background. Typically found in the contents of a VCS_renderpanel.
 */
typedef struct VCS_dynchar {
  /** The character to render. */
  char c;
  /** The shader used to draw the character's foreground (the pixels that correspond to the character itself) */
  VCS_cpushader fg;
  /** The shader used to draw the character's background (the pixels that are in the character's grid space, but aren't used to draw the character) */
  VCS_cpushader bg;
  /** A pointer which is passed to the foreground shader. Used in the case of shaders that rely on external info. */
  void* fgarg;
  /** A pointer which is passed to the background shader. Used in the case of shaders that rely on external info. */
  void* bgarg;
} VCS_dynchar_t;

/**
 * Constructs a VCS_dynchar and returns it by value.
 * \public \relates VCS_dynchar
 * \param[in] c The character to render.
 * \param[in] fg A pointer to the VCS_cpushader with which to render the foreground.
 * \param[in] bg A pointer to the VCS_cpushader with which to render the background.
 * \param[in] fgarg A void pointer which will be passed to the foreground shader as the argument when this character is rendered. May be NULL.
 * \param[in] bgarg Like fgarg, but passed to the background shader.
 * \returns A VCS_dynchar. Note that is is passed by value, not by reference.
 */
VCS_dynchar_t VCS_make_dynchar(char c, VCS_cpushader fg, VCS_cpushader bg, void* fgarg, void* bgarg);

/** A built-in cpushader. Unconditionally returns a black pixel. \relates VCS_dynchar */
uint32_t VCS_blackshader(int x, int y, void* arg);
/** A built-in cpushader. Unconditionally returns a white pixel. \relates VCS_dynchar */
uint32_t VCS_whiteshader(int x, int y, void* arg);

/** A static variable holding a VCS_dynchar which is rendered as a black square. When a VCS_renderpanel is cleared, its characters are all set to this. \relates VCS_dynchar */
static VCS_dynchar_t CHBLANK = (VCS_dynchar_t){' ',VCS_whiteshader,VCS_blackshader,NULL,NULL};
