#pragma once

#include "Renderer.h"
#include "window/ApplicationWindow.h"

class Engine {
    private:
        Renderer renderer;
        ApplicationWindow app_window;


    public:
        Engine(int width, int height) : renderer(width, height), app_window(width, height, "Default Title", renderer.get_front_buffer()) {
            app_window.init();
        }

        /**
         * @brief Moves renderer state forward
         */
        void tick();

        /**
         * @brief Draws a primitive
         */
        void draw(Primitive);

        /**
         * @brief Gets if engine is active and running
         */
        bool is_active() const;

        /**
         * @brief Adds a event handler for the corresponding event type
         */
        void add_event_handler(EVENT_TYPE, std::function<void(MouseState)>);
};