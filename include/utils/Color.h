
#include <cstdint>

/**
 * @class Represents a color in RGB format
 */
struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;

    Color() : red(0), green(0), blue(0), alpha(0) {}
    Color(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue), alpha(0xFF) {}

    /**
     * @brief Converts object into ARGB32 format
     */
    uint32_t to_hex() const {
        return (alpha << 24) | (red << 16) | (green << 8) | blue;
    }
};