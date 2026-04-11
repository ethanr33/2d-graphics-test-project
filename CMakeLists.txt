
cmake_minimum_required(VERSION 3.23)

project(2dRenderer)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


add_executable(out)
add_library(2d-renderer)
add_library(xdg-shell)

find_package(Wayland REQUIRED)

target_sources(xdg-shell
    PRIVATE 
        external/xdg-shell/xdg-shell-protocol.c

    PUBLIC 
        FILE_SET HEADERS 
        BASE_DIRS
            external/xdg-shell  
        FILES
            external/xdg-shell/xdg-shell-client-protocol.h
)


target_sources(2d-renderer
    PRIVATE
        src/Renderer.cpp
        src/ApplicationWindow.cpp

    PUBLIC 
        FILE_SET HEADERS 
        BASE_DIRS 
            include
        FILES 
            include/Renderer.h
            include/FrameBuffer.h
            include/command_processing/Command.h
            include/command_processing/CommandProcessor.h
            include/command_processing/CommandStream.h
            include/primitives/Primitive.h
            include/primitives/Vertex.h
            include/rasterizer/Fragment.h
            include/rasterizer/Rasterizer.h
            include/transformations/ViewportTransformation.h
            include/window/ApplicationWindow.h
)

target_sources(out
    PRIVATE 
        main.cpp
        ${WAYLAND_INCLUDE_DIRS}
)

target_link_libraries(out
    PRIVATE
        xdg-shell
        2d-renderer
        ${WAYLAND_LIBRARIES}
)