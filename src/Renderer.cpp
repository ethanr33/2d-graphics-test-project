
#include "Renderer.h"


void Renderer::display() {
    // 1. Process primitives from command stream
}


void Renderer::clear() {

}

void Renderer::add(Vertex v1) {
    command_stream.add_primitive(v1);
}

