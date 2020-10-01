#include "util/color.h"

/* A sequence of characters printed before input. */
extern char *ps1_seq;

/**
 * Sets the ps1 to the given string.
 * NOTE: str should have a ' ' (space) postfix - such formatting will not be
 * automatically applied.
 *
 * @param str the string that the ps1 should be set to
 */
void set_ps1(char *str);

/**
 * Sets the ps1 to the given color.
 *
 * @param color the color to which the ps1 should be set
 */
void set_ps1_color(Color color);

/**
 * Resets the color of the ps1.
 */
void reset_ps1_color();
