
#pragma once 

#include "primitives/Vertex.h"
#include "command_processing/CommandStream.h"
#include "transformations/TransformationManager.h"
#include "rasterizer/Rasterizer.h"
#include "FrameBuffer.h"
#include "window/ApplicationWindow.h"

class Renderer {
    private:
        int display_width;
        int display_height;

        CommandStream command_stream;
        TransformationManager transformation_manager;
        Rasterizer rasterizer;
        
        FrameBuffer front_buffer;
        FrameBuffer back_buffer;
    public:
        Renderer(int width, int height) : display_width(width), display_height(height), front_buffer(width, height), back_buffer(width, height) {}

        /**
         * @brief Clears back frame buffer, resets command stream
         */
        void clear();

        /**
         * @brief Adds a new primitive to command stream
         */
        void add_primitive(const Primitive&);

        /**
         * @brief Updates front frame buffer with the most recent primitives added since last clear()
        */
        void display();

        /**
         * @brief Gets front buffer for rendering
         */
        const FrameBuffer* get_front_buffer() const;
};