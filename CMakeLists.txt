
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
        src/FrameBuffer.cpp
        src/Engine.cpp
    PUBLIC 
        FILE_SET HEADERS 
        BASE_DIRS 
            include
        FILES 
            include/Renderer.h
            include/FrameBuffer.h
            include/Engine.h
            include/command_processing/Command.h
            include/command_processing/CommandProcessor.h
            include/command_processing/CommandStream.h
            include/primitives/Primitive.h
            include/primitives/Vertex.h
            include/rasterizer/Fragment.h
            include/rasterizer/Rasterizer.h
            include/transformations/ViewportTransformation.h
            include/window/ApplicationWindow.h
            include/window/MouseEvent.h
            include/utils/SignalHandler.h
)

target_sources(out
    PRIVATE 
        ${WAYLAND_CLIENT_INCLUDE_DIR}
        main.cpp
)

target_link_libraries(out
    PRIVATE
        2d-renderer
        xdg-shell
        ${WAYLAND_CLIENT_LIBRARY}
)