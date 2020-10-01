#include "util/color.h"

/* The ps1 */
char *ps1_seq;

/* Characters prepended to the ps1_seq (e.g., color data). */
char *prefix;

/**
 * Sets the ps1_seq to the given string.
 * NOTE: str should have a ' ' (space) postfix - such formatting will not be
 * automatically applied.
 *
 * @param str the string that the ps1_seq should be set to
 */
void set_ps1(char *str)
{
    ps1_seq = str;
}

/**
 * Sets the ps1_seq to the given color.
 *
 * @param color the color to which the ps1_seq should be set
 */
void set_ps1_seq_color(Color color)
{
    switch (color) {
        case Red:
            ps1_seq = "[0;31m";
            return;
        case Green:
            ps1_seq = "[0;32m";
            return;
        case Yellow:
            ps1_seq = "[0;33m";
            return;
        case Blue:
            ps1_seq = "[0;34m";
            return;
        case Magenta:
            ps1_seq = "[0;35m";
            return;
        case Cyan:
            ps1_seq = "[0;36m";
            return;
        default:
            return;
    }
}

/**
 * Resets the color of the ps1_seq.
 */
void reset_ps1_seq_color()
{
    ps1_seq = "[0m";
}
