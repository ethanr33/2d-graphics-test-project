#pragma once

#include <cstdint>

/**
 * @brief Data passed to event handlers when the mouse is clicked
 */
struct MouseState {
    /**
     * x and y positions (relative to top-left of screen) of mouse when event occurs
     */
    uint32_t x;
    uint32_t y;

    MouseState() : x(0), y(0) {}
    MouseState(int x, int y) : x(x), y(y) {}
};