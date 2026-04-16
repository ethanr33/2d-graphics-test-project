
#include "Renderer.h"
#include "window/ApplicationWindow.h"

int main() {

    int width = 1000;
    int height = 500;

    Renderer r(width, height);

    FrameBuffer buffer(width, height);
    
    ApplicationWindow window(width, height, "Window", &buffer);
    window.init();

    while (window.dispatch()) {
        /* This space deliberately left blank */

    }

    return 0;

}