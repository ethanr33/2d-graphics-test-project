
#include "utils/Color.h"

/**
 * @brief Represents information on how to shade a single pixel
 */
struct Fragment {
    uint32_t x;
    uint32_t y;
    Color color;

    Fragment(int x, int y, Color color) : x(x), y(y), color(color) {}
};