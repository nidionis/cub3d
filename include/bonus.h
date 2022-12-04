#include <cub3d.h>

/* put here filenames separated by ',' 
 * the solids MUST be represented by 4 (files) textures
 * even if they come from the same file
 * The identifier in map_case MUST follow the ascii table
 * 0 and 1 are in the mandatory part
 * So the first to the fourth filenames will represent mapcase 2
 * the fifth to the neinth filenames will represents mapcase 3 and so on
 * see add_obstacle function (using map_case - '2' to get the texture index)
 * */

#define BONUS_TEXTURES_SOLIDS "./asserts/text1.xpm,./asserts/text1.xpm,./asserts/text1.xpm,./asserts/text1.xpm"

