
#include "window/ApplicationWindow.h"

int main() {
    
    ApplicationWindow window(800, 800, "Window");
    window.init();
    window.draw();

    while (window.dispatch()) {
        /* This space deliberately left blank */
    }

    return 0;

}