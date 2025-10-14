#pragma once
#include "VCS_dynchar.h"

/**
 * A renderpanel is the primary data structure used to store information about what to draw to the screen.
 * It consists of an array to store VCS_dynchar structs which can either be used to render to the screen or 
 * written to a different VCS_renderpanel.
 *
 * A VCS_renderpanel is typically constructed with VCS_make_rp() and destroyed by calling VCS_rp_free_contents() and then free()
 * on a pointer to the renderpanel. VCS_rp_set() is the typical way to edit the contents in order to draw to the renderpanel.
 *
 * \note A special VCS_renderpanel is created by VCS_init() and stored as VCS_info.rp. It is automatically destroyed along with all the
 * other fields of the VCS_info struct by VCS_quit(), so there is no need to call VCS_rp_free_contents() on it.
 * This special renderpanel is read by VCS_update() to decide what to actually draw to
 * the screen, so anything you want displayed must be written to it eventually.
 */
typedef struct VCS_renderpanel {
  /** The width of the renderpanel. Set automatically by VCS_make_rp(). */
  int width; 
  /** The height of the renderpanel. Set automaticall by VCS_make_rp(). */
  int height; 
  /** The contents of the renderpanel. Do not edit manually; use VCS_rp_set(). */
  VCS_dynchar_t* content; 
} VCS_renderpanel_t;

/**
 * Initializes a VCS_renderpanel given a pointer to an uninitialized one.
 * \private \relates VCS_renderpanel
 * \param[in,out] rp A pointer to an unitialized VCS_renderpanel.
 * \param[in] width The width to give the initialized renderpanel.
 * \param[in] height The height to give the initialized renderpanel.
 * \see
 * VCS_make_rp()
 * VCS_renderpanel
 */
void VCS_rp_init(VCS_renderpanel_t* rp, int width, int height);

/**
 * Creates and returns a pointer to a new VCS_renderpanel.
 * \public \relates VCS_renderpanel
 * \param[in] width The width to give the initialized renderpanel.
 * \param[in] height The height to give the initialized renderpanel.
 * \return
 * Returns a pointer to a VCS_renderpanel.
 * You are expected to free its contents with VCS_rp_free_contents(), and
 * the pointer itself with free().
 *
 * \see
 * VCS_renderpanel
 */
VCS_renderpanel_t* VCS_make_rp(int width, int height);

/**
 * Sets a character in a given VCS_renderpanel to a given VCS_dynchar_t.
 * \public \relates VCS_renderpanel
 * \param[in,out] rp the renderpanel to edit.
 * \param[in] x The x position of the character to set, where far left is 0.
 * \param[in] y The y position of the character to set, where top is 0.
 * \param[in] c A VCS_dynchar_t to set the character to.
 * \see
 * VCS_dynchar_t,
 * VCS_make_dynchar()
 */
void VCS_rp_set(VCS_renderpanel_t* rp, int x, int y, VCS_dynchar_t c);

/**
 * Draws a VCS_renderpanel onto another VCS_renderpanel with optional transparency.
 * Useful for windows, widgets, etc.
 * \public \relates VCS_renderpanel
 * \param[in] source The renderpanel to use as a drawing source.
 * \param[out] dest The renderpanel which will be drawn on.
 * \param[in] x The x position of `dest` on which to place the top-left corner of `source`, where far left is 0.
 * \param[in] y The y position of `dest` on which to place the top-left corner of `source`, where top is 0.
 * \param[in] transparent A value of 1 will cause all space characters in `src` to not replace characters in `dest`. A value of 0 disables this.
 */
void VCS_rp_drawto(VCS_renderpanel_t* source, VCS_renderpanel_t* dest, int x, int y, int transparent);

/**
 * Sets every character in a given VCS_renderpanel to CHBLANK.
 * \public \relates VCS_renderpanel
 * \param[in,out] rp The renderpanel to clear.
 * \see CHBLANK
 */
void VCS_rp_clear(VCS_renderpanel_t* rp);

/**
 * Frees the contents of a given VCS_renderpanel.
 * You must still free the pointer to the renderpanel itself with free().
 * \public \relates VCS_renderpanel
 * \param[in,out] rp The renderpanel of which to free the contents.
 * \see VCS_renderpanel
 */
void VCS_rp_free_contents(VCS_renderpanel_t* rp);
