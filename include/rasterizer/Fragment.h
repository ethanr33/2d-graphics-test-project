
#include "utils/Color.h"

/**
 * @brief Represents information on how to shade a single pixel
 */
struct Fragment {
    // int16_t provides a good range for values while also reducing memory usage
    int32_t x;
    int32_t y;
    Color color;

    Fragment(int32_t x, int32_t y, Color color) : x(x), y(y), color(color) {}
};